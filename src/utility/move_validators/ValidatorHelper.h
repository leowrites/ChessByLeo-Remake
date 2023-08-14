//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once
#include "src/utility/utility.h"
#include "src/entity/board/Board.h"

namespace Chess
{
    bool DestinationIsEnemyOrEmpty(GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateHorizontal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateVertical(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
    bool ValidateDiagonal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board);
    bool PieceInBetweenHorizontal(GridPosPtr& start, GridPosPtr& end, Board& board);
    bool PieceInBetweenVertical(GridPosPtr& start, GridPosPtr& end, Board& board);
    bool PieceInBetweenDiagonal(GridPosPtr& start, GridPosPtr& end, Board& board, int8_t xDir, int8_t yDir);
}
