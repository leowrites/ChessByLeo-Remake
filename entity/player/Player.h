//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once

#include <iostream>
#include <utility>
#include "../piece/Piece.h"

namespace Chess
{
    const std::uint8_t MAX_PLAYER_CHESS_PIECES { 16 };

    enum class PlayerRole
    {
        Black, White
    };

    class Player {
    private:
        const PlayerRole m_playerRole;
        std::array<std::shared_ptr<Piece>, MAX_PLAYER_CHESS_PIECES> m_playerPieces;
        Piece m_playerSelectedPiece {};
    public:
        Player(PlayerRole playerRole,
               std::array<std::shared_ptr<Piece>, MAX_PLAYER_CHESS_PIECES> playerPieces, Piece&)
               : m_playerRole { playerRole }, m_playerPieces {std::move( playerPieces )},
               m_playerSelectedPiece { playerPieces } { };
    };
}
