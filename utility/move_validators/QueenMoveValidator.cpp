//
// Created by Siqi Liu on 2023-07-29.
//

#include "QueenMoveValidator.h"

bool Chess::QueenMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board &board)
{
    return ValidateDiagonal(start, end, playerRole, board) || ValidateHorizontal(start, end, playerRole, board) ||
    ValidateVertical(start, end, playerRole, board);
}
