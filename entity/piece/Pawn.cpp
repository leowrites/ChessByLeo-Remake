//
// Created by Siqi Liu on 2023-07-27.
//

#include "Pawn.h"

namespace Chess
{
    Pawn::Pawn(ChessPieceType chessPieceType, PlayerRole playerRole,
               const std::string_view& unselectedPath,
               const std::string_view& selectedPath, Vector2& initialPosition
//               const std::shared_ptr<MoveValidator>& validator
               )
    : Piece(chessPieceType, playerRole, unselectedPath, selectedPath, initialPosition
//            validator
            )
    {

    }
}