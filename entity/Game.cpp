//
// Created by Siqi Liu on 2023-07-14.
//

#include "Game.h"

#include <utility>

Chess::Game::Game(Chess::GameState gameState, Chess::Board board, GameConfiguration gameConfiguration,
                  const Chess::Players& players, Players mPlayers)
                  : m_gameState { gameState }, m_board { board }, m_currentPlayer { PlayerRole:: White },
                    m_players(std::move(mPlayers)) {

}
