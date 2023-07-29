//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once
#include "board/Board.h"
#include "GameConfiguration.h"
#include "iostream"
#include "player/Player.h"
#include "raylib.h"
#include <ctime>

namespace Chess
{
    enum class GameState
    {
        Loading, Home, Configuration, InGame, Paused, GameOver, Statistics
    };

    using Players = std::pair<Player, Player>;

    class Game {
    private:
        Board m_board;
        GameConfiguration m_gameConfiguration;
        Players m_players;
        PlayerRole m_currentPlayer { PlayerRole::White };
        std::time_t m_lastRecordedTime{ };
        // time since last move = current time - last recorded time
        // if time since last move > configuration time, player has run out of time
        std::time_t m_timeSinceLastMove{ };
        // initialize players
        std::shared_ptr<Piece> m_currentlySelectedPiece { nullptr };

    public:
        Game();
        explicit Game(GameConfiguration& gameConfiguration, PlayerRole currentPlayer=PlayerRole::White);
        Board& GetBoard() { return m_board; };
        void UpdateCurrentlySelectedPiece(std::shared_ptr<Piece>);
        std::shared_ptr<Piece> GetCurrentlySelectedPiece();
    };
}
