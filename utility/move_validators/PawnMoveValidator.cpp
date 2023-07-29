//
// Created by Siqi Liu on 2023-07-29.
//

#include "PawnMoveValidator.h"

namespace Chess
{
    bool Chess::PawnMoveValidator::validate(GridPos &start, GridPos &end, PlayerRole playerRole, Board& board) {
        // pawn can move one/two step forward if it hasn't been moved, it can move diagonal if there is an enemy piece
        // assume white is always on the bottom
        if (playerRole == PlayerRole::White && start->second == 6)
        {
            if ((end->second == 5 || end->second == 4) && end->first == start->first)
            {
                std::cout << "Valid Move";
                return true;
            }
        }

        return false;
    }
}
