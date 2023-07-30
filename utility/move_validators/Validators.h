//
// Created by Siqi Liu on 2023-07-29.
//

#pragma once

#include "PawnMoveValidator.h"
#include "KnightMoveValidator.h"
#include "MoveValidator.h"
#include "utility/utility.h"
#include <iostream>


namespace Chess
{
    // don't like how this is allocated every time
    std::unique_ptr<MoveValidator> GetValidatorByChessPieceType(ChessPieceType pieceType);
}

