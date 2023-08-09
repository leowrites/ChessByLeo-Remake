//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once

#include <iostream>
#include "src/utility/utility.h"
#include "src/entity/piece/Piece.h"

namespace Chess
{
    const std::uint8_t MAX_PLAYER_CHESS_PIECES { 16 };

    class Piece;

    class Player {
    private:
        PlayerRole m_playerRole;
        std::array<std::shared_ptr<Piece>, MAX_PLAYER_CHESS_PIECES> m_playerPieces;
        std::shared_ptr<Piece> m_playerSelectedPiece;
    public:
        Player();
        explicit Player(PlayerRole playerRole);
        void UpdatePlayerRole(PlayerRole playerRole) { m_playerRole = playerRole; };
    };
}
