//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once
#include "MoveValidator.h"
#include "ValidatorHelper.h"

namespace Chess
{
    class RookMoveValidator: public MoveValidator
    {
    public:
        RookMoveValidator() = default;
        bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) override;
        ~RookMoveValidator() override = default;
    };
}
