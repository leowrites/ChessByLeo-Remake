//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once
#include "utility/utility.h"
#include "entity/board/Board.h"

namespace Chess
{
    bool DestinationIsEnemyOrEmpty(GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateHorizontal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateVertical(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateDiagonal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
}
