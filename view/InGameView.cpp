//
// Created by Siqi Liu on 2023-07-27.
//

#include "InGameView.h"

namespace Chess
{
    std::unique_ptr<std::pair<uint8_t, uint8_t>> CalculateGridPosGivenCoord(int x, int y)
    {
        return std::make_unique<std::pair<uint8_t, uint8_t>>(
                x / SQUARE_PIXEL_SIZE % 8,
                y / SQUARE_PIXEL_SIZE % 8
                );
    }
    void InGameView::Update(const std::shared_ptr<Game>& game)
    {
        std::shared_ptr<Piece> currentlySelectedPiece = game->GetCurrentlySelectedPiece();
        // mouse drag behavior
        if (currentlySelectedPiece != nullptr && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            // each piece needs their own positions instead of relying on the index
            // map mouse position to row/col, get the piece and update the coordinates for that piece
            Vector2 mousePosition { GetMousePosition() };
            currentlySelectedPiece->UpdatePosition(mousePosition.x - 50, mousePosition.y - 50);
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            std::unique_ptr<std::pair<uint8_t, uint8_t>> gridPos { std::move(CalculateGridPosGivenCoord(mousePosition.x, mousePosition.y)) };
            // update selected piece
            game->UpdateCurrentlySelectedPiece(game->GetBoard().GetBoardMatrix().at(gridPos->second).at(gridPos->first));
        } else if (currentlySelectedPiece != nullptr && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            // perform validations here

            // correct position to a nearby square
            std::unique_ptr<std::pair<uint8_t, uint8_t>> newGridPos = CalculateGridPosGivenCoord(
                    currentlySelectedPiece->GetPosition()->x,
                    currentlySelectedPiece->GetPosition()->y
                    );

            currentlySelectedPiece->UpdatePosition(newGridPos->first *  SQUARE_PIXEL_SIZE, newGridPos->second * SQUARE_PIXEL_SIZE);
            game->GetBoard().UpdatePiecePositionInBoard(currentlySelectedPiece, newGridPos);
            game->UpdateCurrentlySelectedPiece(nullptr);
        }
    }

    void InGameView::Render(int screenWidth, int screenHeight, std::shared_ptr<Game> &game)
    {
        Board& board = game->GetBoard();
        for (uint8_t i { 0 }; i < 8; ++i)
        {
            for (uint8_t j { 0 }; j < 8; ++j)
            {
                // render square
                DrawSquare(screenWidth, screenHeight, i, j);
            }
        }
        for (uint8_t i { 0 }; i < 8; ++i)
        {
            for (uint8_t j { 0 }; j < 8; ++j)
            {
                Piece* piece { board.GetBoardMatrix().at(i).at(j).get() };
                // render square
                DrawPiece(screenWidth, screenHeight, piece, game);
            }
        }

    }

    void InGameView::DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col)
    {
        // start from top left (0, 0), calculate the rectangle boxes
        // pixel per square: screenWidth / 8
        // x: pixel per square * col
        // y: pixel per square * row
        // width = height = pixel per square
        Vector2 mousePos { GetMousePosition() };
        auto screenWidthFloat = static_cast<float>(screenWidth);
        Rectangle square = { static_cast<float>(SQUARE_PIXEL_SIZE * row),
                             static_cast<float>(SQUARE_PIXEL_SIZE * col),
                             screenWidthFloat,
                             screenWidthFloat};
        if ((row + col) % 2 == 0) {
            DrawRectangleRec(square, BOARD_LIGHT_TILE);
        } else {
            DrawRectangleRec(square, BOARD_DARK_TILE);
        }
    }

    void InGameView::DrawPiece(int screenWidth, int screenHeight, Piece *piece, const std::shared_ptr<Game>& gamePtr) {
        if (piece)
        {
            // need to know if the piece is currently selected, if so, render selected texture
            if (gamePtr->GetCurrentlySelectedPiece().get() == piece)
                DrawTextureEx(*(piece->GetSelectedTexture()), *piece->GetPosition(), 0.0f, 0.45f, WHITE);
            else
                DrawTextureEx(*(piece->GetUnselectedTexture()), *piece->GetPosition(), 0.0f, 0.45f, WHITE);
        }
    }
}