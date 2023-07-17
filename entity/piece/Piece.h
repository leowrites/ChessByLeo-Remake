//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include "../player/Player.h"
#include <string_view>

namespace Chess {
    using Position = std::pair<int, int>;
    enum class ChessPieceType {
        pawn, rook, bishop, queen, king, knight
    };

    enum class PlayerRole;

    class Piece {
    private:
        const ChessPieceType m_chessPieceType;
        const PlayerRole m_pieceOwner;
        const std::string_view m_pathToSprite;
        const Image m_chessSprite;
        Position m_chessPosition;
    public:
        Piece() = delete;
    };
}
