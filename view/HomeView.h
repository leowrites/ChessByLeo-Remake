//
// Created by Siqi Liu on 2023-07-16.
//

#pragma once

#include "raylib.h"
#include "entity/Game.h"
#include "utility/utility.h"

namespace Chess
{
    class HomeView {
    private:
        static std::unordered_map<HOME_MENU_OPTIONS, std::shared_ptr<Rectangle>> s_menuOptionToRectangle;

    public:
        static void Render(int screenWidth, int screenHeight, Vector2& mousePosition);
        static void HandleMouseClick(Vector2& mousePos, GameState& gameState);
    };
}
