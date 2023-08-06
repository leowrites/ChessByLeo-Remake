//
// Created by Siqi Liu on 2023-07-14.
//

#include "Board.h"

namespace Chess
{
    Board::Board()
    {
        // initialize the pieces here
        InitializeChessPieces(PlayerRole::White);
        InitializeChessPieces(PlayerRole::Black);
    }

    void Board::InsertPieceIntoPieces(const std::shared_ptr<Piece>& piece)
    {
        if (piece->GetPieceOwner() == PlayerRole::White)
        {
            if (m_whitePieces.find(piece->GetPieceType()) == m_whitePieces.end())
                m_whitePieces[piece->GetPieceType()] = std::unordered_set<std::shared_ptr<Piece>> {};
            m_whitePieces[piece->GetPieceType()].insert(piece);
        }
        else
        {
            if (m_blackPieces.find(piece->GetPieceType()) == m_blackPieces.end())
                m_blackPieces[piece->GetPieceType()] = std::unordered_set<std::shared_ptr<Piece>> {};
            m_blackPieces[piece->GetPieceType()].insert(piece);
        }
    }

    void Board::InitializeChessPieces(PlayerRole playerRole)
    {
        uint8_t row{7};
        int8_t pawnDirection{-1};
        Vector2 position;
        if (playerRole == PlayerRole::Black) {
            pawnDirection = 1;
            row = 0;
        }

        for (uint8_t col{0}; col < 8; ++col) {
            position = {100.0f * col, 100.0f * row};
            switch (col) {
                case 0:
                case 7:
                    if (playerRole == PlayerRole::White) {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::rook, playerRole,
                                                                    whiteRookUnselected,
                                                                    whiteRookSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    } else {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::rook, playerRole,
                                                                    blackRookUnselected,
                                                                    blackRookSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    }
                    break;
                case 1:
                case 6:
                    if (playerRole == PlayerRole::White) {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::knight, playerRole,
                                                                    whiteKnightUnselected,
                                                                    whiteKnightSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    } else {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::knight, playerRole,
                                                                    blackKnightUnselected,
                                                                    blackKnightSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    }
                    break;
                case 2:
                case 5:
                    if (playerRole == PlayerRole::White) {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::bishop, playerRole,
                                                                    whiteBishopUnselected,
                                                                    whiteBishopSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    } else {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::bishop, playerRole,
                                                                    blackBishopUnselected,
                                                                    blackBishopSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    }
                    break;
                case 3:
                    if (playerRole == PlayerRole::White) {
                        m_whiteKing = std::make_shared<Piece>(ChessPieceType::king, playerRole,
                                                              whiteKingUnselected,
                                                              whiteKingSelected,
                                                              position,
                                                              whiteKingInCheck);
                        m_board[row][col] = m_whiteKing;
                    } else {
                        m_blackKing = std::make_shared<Piece>(ChessPieceType::king, playerRole,
                                                              blackKingUnselected,
                                                              blackKingSelected,
                                                              position,
                                                              blackKingInCheck);
                        m_board[row][col] = m_blackKing;
                    }
                    break;
                case 4:
                    if (playerRole == PlayerRole::White) {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::queen, playerRole,
                                                                    whiteQueenUnselected,
                                                                    whiteQueenSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    } else {
                        m_board[row][col] = std::make_shared<Piece>(ChessPieceType::queen, playerRole,
                                                                    blackQueenUnselected,
                                                                    blackQueenSelected,
                                                                    position);
                        InsertPieceIntoPieces(m_board[row][col]);
                    }
                    break;
                default:
                    break;
            }
        }
        for (uint8_t col{0}; col < 8; ++col) {
            position = Vector2{100.0f * col, 100.0f * (row + pawnDirection)};
            if (playerRole == PlayerRole::White) {
                m_board[row + pawnDirection][col] = std::make_shared<Piece>(ChessPieceType::pawn, playerRole,
                                                                            whitePawnUnselected,
                                                                            whitePawnSelected,
                                                                            position);
                InsertPieceIntoPieces(m_board[row + pawnDirection][col]);
            } else {
                m_board[row + pawnDirection][col] = std::make_shared<Piece>(ChessPieceType::pawn, playerRole,
                                                                            blackPawnUnselected,
                                                                            blackPawnSelected,
                                                                            position);
                InsertPieceIntoPieces(m_board[row + pawnDirection][col]);
            }
        }
    }

    void Board::UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, GridPosPtr& newPos, GridPosPtr& oldPos)
    {
        // use the piece's old position and set that to nullptr
        m_board[newPos->second][newPos->first] = std::move(m_board[oldPos->second][oldPos->first]);
    }
    std::unique_ptr<std::vector<GridPosPtr>> Board::GetAllPossibleHorizontalAndVerticalPositions(const std::shared_ptr<Piece> &piece)
    {
        GridPosPtr currentPos { std::move(CalculateGridPosGivenCoord(piece->GetPosition())) };
        int startX { currentPos->first };
        int startY { currentPos->second };
        std::unique_ptr<std::vector<GridPosPtr>> positions { std::make_unique<std::vector<GridPosPtr>>() };
//        LoopAndAddGridPosToVector(
//                startX, startY, 1, 1, 8, 8, 1, 0, positions, piece->GetPieceOwner()
//                );
        for (int i = 1; startX + i < 8; ++i) {
            if (m_board[currentPos->second][startX + i] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(startX + i, currentPos->second));
            } else if (m_board[currentPos->second][startX + i]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(startX + i, currentPos->second));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startX - i >= 0; ++i) {
            if (m_board[currentPos->second][startX - i] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(startX - i, currentPos->second));
            } else if (m_board[currentPos->second][startX - i]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(startX - i, currentPos->second));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startY + i < 8; ++i) {
            if (m_board[startY + i][currentPos->first] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY + i));
            } else if (m_board[startY + i][currentPos->first]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY + i));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startY - i >= 0; ++i) {
            if (m_board[startY - i][currentPos->first] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY - i));
            } else if (m_board[startY - i][currentPos->first]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY - i));
                break;
            } else {
                break;
            }
        }
        for (auto& pos: *positions)
        {
            std::cout << "Grid(" << (int)pos->first << ", " << (int)pos->second << ")" << std::endl;
        }
        return positions;
    }
    std::unique_ptr<std::vector<GridPosPtr>> Board::GetAllPossibleDiagonalPositions(const std::shared_ptr<Piece> &piece)
    {
        GridPosPtr currentPos { std::move(CalculateGridPosGivenCoord(piece->GetPosition())) };
        int startX { currentPos->first };
        int startY { currentPos->second };
        int currX;
        int currY;
        std::unique_ptr<std::vector<GridPosPtr>> positions { std::make_unique<std::vector<GridPosPtr>>() };
        // bottom right
        for (int i = 1, j = 1; startX + i < 8 && startY + i < 8; ++i, ++j) {
            currX = startX + i;
            currY = startY + j;
            if (m_board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (m_board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // top right
        for (int i = 1, j = 1; startX + i < 8 && startY - j >= 0; ++i, ++j) {
            currX = startX + i;
            currY = startY - j;
            if (m_board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (m_board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // top left
        for (int i = 1, j = 1; startX - i >= 0 && startY - j >= 8; ++i, ++j) {
            currX = startX - i;
            currY = startY - j;
            if (m_board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (m_board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // bottom left
        for (int i = 1, j = 1; startX - i >= 0 && startX + j < 8; ++i, ++j) {
            currX = startX - i ;
            currY = startY + j ;
            if (m_board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (m_board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        for (auto& pos: *positions)
        {
            std::cout << "Grid(" << (int)pos->first << ", " << (int)pos->second << ")" << std::endl;
        }
        return positions;
    }
    std::unique_ptr<std::vector<GridPosPtr>> Board::GetAllPossiblePositionsForPiece(const std::shared_ptr<Piece> &piece) {
        GridPosPtr gridPosPtr { std::move(CalculateGridPosGivenCoord(piece->GetPosition()))};
        switch(piece->GetPieceType())
        {
            case ChessPieceType::rook:
            {
                return GetAllPossibleHorizontalAndVerticalPositions(piece);
            }
            case ChessPieceType::bishop:
            {
                std::cout << "Bishop"<< std::endl;
                return GetAllPossibleDiagonalPositions(piece);
            }
            case ChessPieceType::queen:
            {
                std::cout << "Queen"<< std::endl;
                std::unique_ptr<std::vector<GridPosPtr>> vec1 { std::move(GetAllPossibleHorizontalAndVerticalPositions(piece)) };
                std::unique_ptr<std::vector<GridPosPtr>> vec2 { std::move(GetAllPossibleDiagonalPositions(piece)) };
                vec1->insert(vec1->end(), std::make_move_iterator(vec2->begin()), std::make_move_iterator(vec2->end()));
                return vec1;
            }
            case ChessPieceType::knight:
            {
                std::unique_ptr<std::vector<GridPosPtr>> posPtr { std::make_unique<std::vector<GridPosPtr>>() };
                std::array possiblePos {
                        GridPos {gridPosPtr->first - 1, gridPosPtr->second + 2},
                        GridPos {gridPosPtr->first + 1, gridPosPtr->second + 2},
                        GridPos {gridPosPtr->first - 1, gridPosPtr->second - 2},
                        GridPos {gridPosPtr->first + 1, gridPosPtr->second - 2},
                        GridPos {gridPosPtr->first - 2, gridPosPtr->second + 1},
                        GridPos {gridPosPtr->first + 2, gridPosPtr->second + 1},
                        GridPos {gridPosPtr->first - 2, gridPosPtr->second - 1},
                        GridPos {gridPosPtr->first + 2, gridPosPtr->second - 1}
                };
                for (auto& pos: possiblePos)
                {
                    posPtr->push_back(std::make_unique<GridPos>(pos));
                }
                return posPtr;
            }
            case ChessPieceType::pawn:
            {
                return std::make_unique<std::vector<GridPosPtr>>();
            }
            case ChessPieceType::king:
                return nullptr;
        }
    }
    void Board::LoopAndAddGridPosToVector(int startX, int startY, int startCountX, int startCountY, int endX, int endY,
                                          int incX, int incY, std::unique_ptr<std::vector<GridPosPtr>>& positions, PlayerRole pieceOwner)
    {
        // to go from left to right
        // endX > startX, inc by 1
        // stop when startX + i == 8
        // to go from right to left
        // if endX < startX, dec by 1
        // stop when startX - i == 0
        for (int i = startCountX, j = startCountY; startX + i != endX && startY + j != endY; i += incX, j += incY) {
            int currX { startX + i };
            int currY { startY + j };
            if (m_board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (m_board[currY][currX]->GetPieceOwner() != pieceOwner) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
    }
}
