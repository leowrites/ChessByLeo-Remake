//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include <iostream>
#include <vector>
#include "MoveValidator.h"

namespace Chess
{
    class PawnMoveValidator: public MoveValidator
    {
    public:
        PawnMoveValidator() = default;
        bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) override;
        static std::unique_ptr<std::vector<GridPosPtr>> GetPossibleMoves(GridPosPtr& start, PlayerRole playerRole, BoardMatrix& board);
        ~PawnMoveValidator() override = default;
    };
}
