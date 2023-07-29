//
// Created by Siqi Liu on 2023-07-14.
//

#include "Board.h"
#include "utility/move_validators/Validators.h"

namespace Chess
{
    Board::Board()
    {
        // initialize the pieces here
        InitializeChessPieces(PlayerRole::White);
        InitializeChessPieces(PlayerRole::Black);
    }

    void Board::InitializeChessPieces(PlayerRole playerRole) {
        uint8_t row{7};
        int8_t pawnDirection{-1};
        Vector2 position;
        if (playerRole == PlayerRole::Black) {
            pawnDirection = 1;
            row = 0;
        }

        PawnMoveValidator pawnMoveValidator;


        for (uint8_t col{0}; col < 8; ++col) {
            position = {100.0f * col, 100.0f * row};
            switch (col) {
                case 0:
                case 7:
                    if (playerRole == PlayerRole::White)
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   whiteRookUnselected,
                                                                   whiteRookSelected,
                                                                   position);
                    }
                    else
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   blackRookUnselected,
                                                                   blackRookSelected,
                                                                   position);
                    }
                    break;
                case 1:
                case 6:
                    if (playerRole == PlayerRole::White)
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   whiteKnightUnselected,
                                                                   whiteKnightSelected,
                                                                   position);
                    }
                    else
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   blackKnightUnselected,
                                                                   blackKnightSelected,
                                                                   position);
                    }
                    break;
                case 2:
                case 5:
                    if (playerRole == PlayerRole::White)
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   whiteBishopUnselected,
                                                                   whiteBishopSelected,
                                                                   position);
                    }
                    else
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   blackBishopUnselected,
                                                                   blackBishopSelected,
                                                                   position);
                    }
                    break;
                case 3:
                    if (playerRole == PlayerRole::White)
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   whiteKingUnselected,
                                                                   whiteKingSelected,
                                                                   position);
                    }
                    else
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   blackKingUnselected,
                                                                   blackKingSelected,
                                                                   position);
                    }
                    break;
                case 4:
                    if (playerRole == PlayerRole::White)
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   whiteQueenUnselected,
                                                                   whiteQueenSelected,
                                                                   position);
                    }
                    else
                    {
                        m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                   blackQueenUnselected,
                                                                   blackQueenSelected,
                                                                   position);
                    }
                    break;
                default:
                    break;
            }
            for (uint8_t col{0}; col < 8; ++col) {
                position = Vector2{100.0f * col, 100.0f * (row + pawnDirection)};
                if (playerRole == PlayerRole::White)
                {
                    m_board[row + pawnDirection][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                               whitePawnUnselected,
                                                                               whitePawnSelected,
                                                                               position);
                }
                else
                {
                    m_board[row + pawnDirection][col] = std::make_shared<Pawn>(ChessPieceType::pawn, playerRole,
                                                                               blackPawnUnselected,
                                                                               blackPawnSelected,
                                                                               position);
                }
            }
        }
    }

    void Board::UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, GridPos& newPos, GridPos& oldPos)
    {
        // use the piece's old position and set that to nullptr
        m_board[oldPos->second][oldPos->first] = nullptr;
        m_board[newPos->second][newPos->first] = std::move(piece);
    }
}
