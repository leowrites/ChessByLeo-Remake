//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include <iostream>
#include "MoveValidator.h"

namespace Chess
{
    class PawnMoveValidator: public MoveValidator
    {
    public:
        PawnMoveValidator() = default;
        bool validate(GridPos& start, GridPos& end, PlayerRole playerRole, Board& board) override;
        static bool DiagonalEnemyExists(GridPos& end, PlayerRole playerRole, Board& board);
        static bool AbovePieceExists(GridPos& end, Board& board);
        ~PawnMoveValidator() override = default;
    };
}
