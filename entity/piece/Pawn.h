//
// Created by Siqi Liu on 2023-07-27.
//

#pragma once

#include "entity/piece/Piece.h"

namespace Chess
{
    class Pawn: public Piece
    {
    private:
    public:
        Pawn() = default;
        Pawn(ChessPieceType chessPieceType,
             PlayerRole playerRole,
             const std::string_view& unselectedPath,
             const std::string_view& selectedPath,
             Vector2& initialPosition
        );
        std::string_view GetPieceName() override { return "Pawn"; };
        void Render() override {};
    };
}
