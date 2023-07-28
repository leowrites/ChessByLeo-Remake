//
// Created by Siqi Liu on 2023-07-27.
//

#include "Pawn.h"

namespace Chess
{
    Pawn::Pawn(ChessPieceType chessPieceType, PlayerRole playerRole, const std::string_view &imagePath)
    : Piece(chessPieceType, playerRole, imagePath)
    {

    }
}