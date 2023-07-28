//
// Created by Siqi Liu on 2023-07-16.
//

#include "HomeView.h"
#include <iostream>
#include <memory>

namespace Chess
{
    std::unordered_map<HOME_MENU_OPTIONS, std::shared_ptr<Rectangle>> HomeView::s_menuOptionToRectangle;

    void HomeView::Render(const int screenWidth, const int screenHeight, Vector2& mousePosition)
    {
        const char* title { "Chess By Leo V2 "};
        const int titleWidth {MeasureText(title, TITLE_TEXT_FONT_SIZE) };
        const int alignedX { (screenWidth - titleWidth) / 2 };
        DrawText(title,
                 alignedX,
                 (screenHeight - TITLE_TEXT_FONT_SIZE) / 3,
                 TITLE_TEXT_FONT_SIZE,
                 MAROON);
        // the rest of the options
        int index { 1 };
        for (auto& option: HOME_MENU_OPTIONS_ARRAY)
        {
            // if there is no mapping from an option to its rectanlge, calculate it and add it
            const char* text { ToString(option) };
            const int textWidth { MeasureText(text, HOME_MENU_TEXT_FONT_SIZE)  };
            const int textY { (screenHeight - HOME_MENU_TEXT_FONT_SIZE) / 3 + index * ( HOME_MENU_TEXT_FONT_SIZE + 20) };
            Color color { LIGHTGRAY };
            Rectangle rec {
                static_cast<float>(alignedX), static_cast<float>(textY),
                static_cast<float>(textWidth), HOME_MENU_TEXT_FONT_SIZE
            };

            if (s_menuOptionToRectangle.find(option) == s_menuOptionToRectangle.end())
            {
                std::shared_ptr<Rectangle> recPtr { std::make_shared<Rectangle>(rec) };
                s_menuOptionToRectangle.insert({ option, recPtr });
            }

            if (CheckCollisionPointRec(mousePosition, rec))
                color = MAROON;
            DrawText(text, alignedX, textY, HOME_MENU_TEXT_FONT_SIZE, color);
            ++index;
        }
    }

    void HomeView::Update(Vector2& mousePos, GameState& gameState) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            auto it = std::find_if(std::begin(s_menuOptionToRectangle), std::end(s_menuOptionToRectangle),
                         [&mousePos](const std::pair<const HOME_MENU_OPTIONS, std::shared_ptr<Rectangle>>& item)
                         { return CheckCollisionPointRec(mousePos, *(item.second)); }
            );
            if (it != std::end(s_menuOptionToRectangle))
            {
                switch(it->first)
                {
                    case HOME_MENU_OPTIONS::SinglePlayer:
                    case HOME_MENU_OPTIONS::AgainstComputer:
                        gameState = GameState::Configuration;
                        break;
                    case HOME_MENU_OPTIONS::Stats:
                        gameState = GameState::Statistics;
                        break;
                    case HOME_MENU_OPTIONS::Quit:
                        CloseWindow();
                        exit(0);
                    default:
                        break;
                }
            }
        }
    }
}