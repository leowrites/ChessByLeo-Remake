//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include "MoveValidator.h"
#include "algorithm"
#include "array"

namespace Chess
{
    class KingMoveValidator: public MoveValidator
    {
    public:
        KingMoveValidator() = default;
        bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) override;
        ~KingMoveValidator() override = default;
    };
}