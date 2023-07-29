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
//        for (uint8_t row = 0; row < 2; ++row) {
//            for (uint8_t col = 0; col < 8; ++col) {
//                // initialize the first row
//                if (row == 0)
//                {
//
//                }
//                Vector2 position { 100.0f * row, 100.0f * col };
//                m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
//                                                           "../texture/whitePawnIcon.png",
//                                                           "../texture/whitePawnSelected.png",
//                                                           position);
//                // now we need
//            }
//        }
    }

    void Board::InitializeChessPieces(PlayerRole playerRole) {
        // if player role == black, generate row 0 & 1
        // if player role == white, generate row 7 & 8
        // brute forcing for now and will comeback to simplify this
        if (playerRole == PlayerRole::Black)
        {
            Vector2 position { 100.0f * 0, 100.0f * 0};
            m_board[0][0] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                       "../texture/whiteRookIcon.png",
                                                       "../texture/whiteRookSelected.png",
                                                       position);
            position = Vector2 { 100.0f * 1, 100.0f * 0};
            m_board[0][1] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteKnightIcon.png",
                                                   "../texture/whiteKnightSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 2, 100.0f * 0};
            m_board[0][2] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteBishopIcon.png",
                                                   "../texture/whiteBishopSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 3, 100.0f * 0};
            m_board[0][3] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteKingIcon.png",
                                                   "../texture/whiteKingSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 4, 100.0f * 0};
            m_board[0][4] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteQueenIcon.png",
                                                   "../texture/whiteQueenSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 5, 100.0f * 0};
            m_board[0][5] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteBishopIcon.png",
                                                   "../texture/whiteBishopSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 6, 100.0f * 0};
            m_board[0][6] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteKnightIcon.png",
                                                   "../texture/whiteKnightSelected.png",
                                                   position);
            position = Vector2 { 100.0f * 7, 100.0f * 0};
            m_board[0][7] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                   "../texture/whiteRookIcon.png",
                                                   "../texture/whiteRookSelected.png",
                                                   position);
//            m_board[0][0] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
//                                                   "../texture/whitePawnIcon.png",
//                                                   "../texture/whitePawnSelected.png",
//                                                   position);
        }
        else
        {

        }
    }

    void Board::UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, std::unique_ptr<std::pair<uint8_t, uint8_t>>& newPos)
    {
        // update the piece position in the board, and replace the original piece if there was one
        // set the original to empty
        m_board[newPos->second][newPos->first] = std::move(piece);
    }
}
