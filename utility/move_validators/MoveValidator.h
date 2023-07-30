//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include "utility/utility.h"
#include "entity/board/Board.h"

// Interface for a move validator
namespace Chess
{
    class MoveValidator
    {
    protected:
        MoveValidator() = default;
    public:
        virtual bool validate(GridPosPtr& start, GridPosPtr& end, PlayerRole playerRole, Board& board) = 0;
        virtual ~MoveValidator() = default;
    };
}