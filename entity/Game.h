//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once
#include "board/Board.h"
#include "GameConfiguration.h"
#include "iostream"
#include "player/Player.h"
#include "raylib.h"

namespace Chess
{
    enum class GameState
    {
        Loading, Home, Configuration, InGame, Paused, GameOver, Statistics
    };

    using Players = std::pair<Player, Player>;

    class Game {
    private:
        GameState m_gameState;
        Board m_board;
        GameConfiguration m_gameConfiguration;
        Players m_players;
        PlayerRole m_currentPlayer;
        // last time
        // there will be methods to reset the time
        double m_lastRecordedTime{ };
        // time since last move = current time - last recorded time
        // if time since last move > configuration time, player has run out of time
        double m_timeSinceLastMove{ };

    public:
        Game(Chess::GameState gameState, Chess::Board board, GameConfiguration gameConfiguration,
             const Chess::Players& players, Players mPlayers);
    };
}
