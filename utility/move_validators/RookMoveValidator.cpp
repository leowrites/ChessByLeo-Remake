//
// Created by Siqi Liu on 2023-07-29.
//

#include "RookMoveValidator.h"

namespace Chess
{
    bool RookMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board &board)
    {
        if (ValidateHorizontal(start, end, playerRole, board) || ValidateVertical(start, end, playerRole, board))
            return true;
        return false;
    }
}
