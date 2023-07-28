//
// Created by Siqi Liu on 2023-07-17.
//

#pragma once

#include <memory>
#include "entity/Game.h"

namespace Chess
{
    class LoadingView {
    public:
        static void Render(int screenWidth, int screenHeight);
        static void Update(GameState &gameState);
        // Load assets & initialize the game
        static void InitializeGame(std::shared_ptr<Chess::Game>& gamePtr, GameConfiguration& gameConfiguration);
    };
}
