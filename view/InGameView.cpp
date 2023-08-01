//
// Created by Siqi Liu on 2023-07-27.
//

#include "InGameView.h"

namespace Chess {
    void InGameView::Update(const std::shared_ptr<Game> &game) {
        std::shared_ptr<Piece> currentlySelectedPiece = game->GetCurrentlySelectedPiece();
        // mouse drag behavior
        if (currentlySelectedPiece != nullptr && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // each piece needs their own positions instead of relying on the index
            // map mouse position to row/col, get the piece and update the coordinates for that piece
            Vector2 mousePosition{GetMousePosition()};
            currentlySelectedPiece->UpdatePosition(mousePosition.x, mousePosition.y);
        } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            GridPosPtr gridPos{std::move(CalculateGridPosGivenCoord(mousePosition.x, mousePosition.y))};
            // update selected piece
            // if clicked on is not null, update old position
//            if (game->GetBoard().GetBoardMatrix().at(gridPos->second).at(gridPos->first) &&
//                game->GetBoard().GetBoardMatrix().at(gridPos->second).at(gridPos->first)->GetPieceOwner() ==
//                game->GetCurrentPlayer()) {
                game->UpdateCurrentlySelectedPiece(
                        game->GetBoard().GetBoardMatrix().at(gridPos->second).at(gridPos->first));
                // only current player can be selected, check which player the piece belongs to
                if (game->GetCurrentlySelectedPiece() != nullptr) {
                    game->GetCurrentlySelectedPiece()->UpdateOldPosition(gridPos->first % 8 * 100,
                                                                         gridPos->second % 8 * 100);
//                }
            }
        } else if (currentlySelectedPiece != nullptr && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            // perform validations here
            // correct position to a nearby square
            GridPosPtr newGridPos{std::move(CalculateGridPosGivenCoord(
                    currentlySelectedPiece->GetPosition()->x,
                    currentlySelectedPiece->GetPosition()->y
            ))};
            GridPosPtr oldGridPos{std::move(CalculateGridPosGivenCoord(
                    currentlySelectedPiece->GetOldPosition()->x,
                    currentlySelectedPiece->GetOldPosition()->y
            ))};

            std::unique_ptr<MoveValidator> validator{
                    std::move(GetValidatorByChessPieceType(currentlySelectedPiece->GetPieceType()))};
            if (validator && validator->validate(oldGridPos, newGridPos, currentlySelectedPiece->GetPieceOwner(),
                                                 game->GetBoard())) {
                currentlySelectedPiece->UpdatePosition(newGridPos->first * SQUARE_PIXEL_SIZE,
                                                       newGridPos->second * SQUARE_PIXEL_SIZE);
                game->GetBoard().UpdatePiecePositionInBoard(currentlySelectedPiece, newGridPos, oldGridPos);
                game->UpdateCurrentlySelectedPiece(nullptr);
                // update current player to the other
                game->UpdateCurrentPlayer(
                        game->GetCurrentPlayer() == PlayerRole::Black ? PlayerRole::White : PlayerRole::Black);
                // after a move is made, check if the other player is now being checked
                const std::shared_ptr<Piece> &whiteKing{game->GetBoard().GetWhiteKing()};
                whiteKing->UpdateInCheck(IsKingInCheck(PlayerRole::White, (Game &) game, game->GetBoard()));

                const std::shared_ptr<Piece> &blackKing{game->GetBoard().GetBlackKing()};
                blackKing->UpdateInCheck(IsKingInCheck(PlayerRole::Black, (Game &) game, game->GetBoard()));
            } else {
                // reset to old position
                currentlySelectedPiece->UpdatePosition(currentlySelectedPiece->GetOldPosition()->x,
                                                       currentlySelectedPiece->GetOldPosition()->y);
                game->UpdateCurrentlySelectedPiece(nullptr);
            }
        }
    }

    void InGameView::Render(int screenWidth, int screenHeight, std::shared_ptr<Game> &game) {
        Board &board = game->GetBoard();
        for (uint8_t i{0}; i < 8; ++i) {
            for (uint8_t j{0}; j < 8; ++j) {
                // render square
                DrawSquare(screenWidth, screenHeight, i, j);
            }
        }
        for (uint8_t i{0}; i < 8; ++i) {
            for (uint8_t j{0}; j < 8; ++j) {
                Piece *piece{board.GetBoardMatrix().at(i).at(j).get()};
                // render square
                if (piece != game->GetCurrentlySelectedPiece().get())
                    DrawPiece(screenWidth, screenHeight, piece, game);
            }
        }
        // render currently selected last
        if (game->GetCurrentlySelectedPiece())
            DrawPiece(screenWidth, screenHeight, game->GetCurrentlySelectedPiece().get(), game);
    }

    void InGameView::DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col) {
        // start from top left (0, 0), calculate the rectangle boxes
        // pixel per square: screenWidth / 8
        // x: pixel per square * col
        // y: pixel per square * row
        // width = height = pixel per square
        Vector2 mousePos{GetMousePosition()};
        auto screenWidthFloat = static_cast<float>(screenWidth);
        Rectangle square = {static_cast<float>(SQUARE_PIXEL_SIZE * col),
                            static_cast<float>(SQUARE_PIXEL_SIZE * row),
                            screenWidthFloat,
                            screenWidthFloat};
        if ((row + col) % 2 == 0) {
            DrawRectangleRec(square, BOARD_LIGHT_TILE);
        } else {
            DrawRectangleRec(square, BOARD_DARK_TILE);
        }
    }

    void InGameView::DrawPiece(int screenWidth, int screenHeight, Piece *piece, const std::shared_ptr<Game> &gamePtr) {
        if (piece) {
            // need to know if the piece is currently selected, if so, render selected texture
            if (gamePtr->GetCurrentlySelectedPiece().get() == piece) {
                Vector2 drawPos{GetMousePosition()};
                drawPos.x -= 50;
                drawPos.y -= 50;
                DrawTextureEx(*(piece->GetSelectedTexture()), drawPos, 0.0f, 0.45f, WHITE);
            } else if (piece->GetPieceType() == ChessPieceType::king && piece->GetInCheck()) {
                DrawTextureEx(*(piece->GetInCheckTexture()), *piece->GetPosition(), 0.0f, 0.45f, WHITE);
            } else {
                DrawTextureEx(*(piece->GetUnselectedTexture()), *piece->GetPosition(), 0.0f, 0.45f, WHITE);
            }
        }
    }
}