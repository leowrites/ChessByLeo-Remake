//
// Created by Siqi Liu on 2023-07-13.
//

#include "Player.h"


namespace Chess
{
    Player::Player(Chess::PlayerRole playerRole): m_playerRole(playerRole)
    {
        // initialize the pieces
    }

    // default initialize player role to white
    Player::Player(): m_playerRole { PlayerRole::White }
    {

    }
}