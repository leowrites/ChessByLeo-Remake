//
// Created by Siqi Liu on 2023-07-16.
//

#pragma once

#include <iostream>
#include "raylib.h"

namespace Chess
{
    using GridPos = std::unique_ptr<std::pair<uint8_t, uint8_t>>;
    constexpr int SCREEN_WIDTH { 800 };
    constexpr int SCREEN_HEIGHT { 800 };
    constexpr int SCREEN_PADDING_X { SCREEN_WIDTH / 16 };
    constexpr int SCREEN_PADDING_Y { SCREEN_HEIGHT / 16 };
    constexpr int TITLE_TEXT_FONT_SIZE { 50 };
    constexpr int HOME_MENU_TEXT_FONT_SIZE { 30 };
    constexpr int SQUARE_PIXEL_SIZE { SCREEN_WIDTH / 8 };
    constexpr int MENU_SPACING { 20 };
    constexpr Color BOARD_LIGHT_TILE { 103, 101, 47, 100 };
    constexpr Color BOARD_DARK_TILE { 255, 225, 206, 100 };
    enum class HOME_MENU_OPTIONS
    {
        SinglePlayer, AgainstComputer, Stats, Quit
    };
    const HOME_MENU_OPTIONS HOME_MENU_OPTIONS_ARRAY[] { HOME_MENU_OPTIONS::SinglePlayer,
                                                        HOME_MENU_OPTIONS::AgainstComputer,
                                                        HOME_MENU_OPTIONS::Stats,
                                                        HOME_MENU_OPTIONS::Quit};
    char* ToString(HOME_MENU_OPTIONS homeMenuOptions);
    enum class PlayerRole
    {
        Black, White
    };
}