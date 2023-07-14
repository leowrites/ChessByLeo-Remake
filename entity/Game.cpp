//
// Created by Siqi Liu on 2023-07-14.
//

#include "Game.h"

Chess::Game::Game(Chess::GameState gameState, Chess::Board board, GameConfiguration gameConfiguration,
                  Chess::Players players)
                  : m_gameState { gameState }, m_board { board }, m_currentPlayer { PlayerRole:: White }
{

}
