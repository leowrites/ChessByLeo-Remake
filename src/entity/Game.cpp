//
// Created by Siqi Liu on 2023-07-14.
//

#include "Game.h"

#include <utility>

namespace Chess
{
    Game::Game()
    {
        // update one of the player to black
        m_players.second.UpdatePlayerRole(PlayerRole::Black);
    }

    Game::Game(GameConfiguration &gameConfiguration, PlayerRole currentPlayer)
    : m_currentPlayer { currentPlayer }, m_gameConfiguration { gameConfiguration },
     m_players { Player{PlayerRole::White}, Player { PlayerRole::Black } }
     {

    }

    void Game::UpdateCurrentlySelectedPiece(std::shared_ptr <Piece> piece) {
        // this may be a problem if the old piece still needs it
        m_currentlySelectedPiece = std::move(piece);
    }

    std::shared_ptr <Piece> Game::GetCurrentlySelectedPiece() {
        return m_currentlySelectedPiece;
    };
}