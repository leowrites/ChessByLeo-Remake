//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include "MoveValidator.h"
#include "algorithm"
#include "array"

namespace Chess
{
    class KnightMoveValidator: public MoveValidator
    {
    public:
        KnightMoveValidator() = default;
        bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) override;
        static std::unique_ptr<std::vector<GridPosPtr>> GetPossibleMoves(GridPosPtr& start, PlayerRole playerRole, BoardMatrix& board);
        ~KnightMoveValidator() override = default;
    };
}
