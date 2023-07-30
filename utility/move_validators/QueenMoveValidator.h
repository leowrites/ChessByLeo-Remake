//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once
#include "MoveValidator.h"
#include "ValidatorHelper.h"

namespace Chess
{
    class QueenMoveValidator: public MoveValidator
    {
    public:
        QueenMoveValidator() = default;
        bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) override;
        ~QueenMoveValidator() override = default;
    };
}
