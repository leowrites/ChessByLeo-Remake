//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include "PawnMoveValidator.h"
#include "KnightMoveValidator.h"
#include "KingMoveValidator.h"
#include "RookMoveValidator.h"
#include "QueenMoveValidator.h"
#include "BishopMoveValidator.h"
#include "MoveValidator.h"
#include "src/utility/utility.h"
#include <iostream>


namespace Chess
{
    // don't like how this is allocated every time
    std::unique_ptr<MoveValidator> GetValidatorByChessPieceType(ChessPieceType pieceType);
}

