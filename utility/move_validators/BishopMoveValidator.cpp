//
// Created by Siqi Liu on 2023-07-29.
//

#include "BishopMoveValidator.h"

bool Chess::BishopMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board &board)
{
    return ValidateDiagonal(start, end, playerRole, board);
}
