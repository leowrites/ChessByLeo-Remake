//
// Created by Siqi Liu on 2023-07-17.
//

#pragma once

#include "entity/GameConfiguration.h"
#include "entity/Game.h"

namespace Chess
{
    class GameConfigView {
    private:
        static int s_selectedComputerDifficulty;
        static bool s_showDifficultyDropdownBox;
        static int s_selectedGameTime;
        static bool s_showGameTimeDropBox;
        static const std::string_view s_gameTimeOptions;
        static bool s_clickedNext;
    public:
        static void Update(Vector2& mousePosition, GameConfiguration& gameConfiguration, GameState& gameState);
        static void Reset();
        static void Render();
    };
}
