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
}
