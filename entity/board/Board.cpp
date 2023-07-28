//
// Created by Siqi Liu on 2023-07-14.
//

#include "Board.h"

Chess::Board::Board()
{
    // initialize the pieces here
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            m_board[row][col] = std::make_shared<Pawn>(ChessPieceType::pawn, PlayerRole::White,
                                                       "../texture/whitePawnIcon.png");;
        }
    }
}
