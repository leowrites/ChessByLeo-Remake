//
// Created by Siqi Liu on 2023-07-16.
//

#pragma once

#include <iostream>
#include "raylib.h"

namespace Chess
{
    const int TITLE_TEXT_FONT_SIZE { 50 };
    const int HOME_MENU_TEXT_FONT_SIZE { 30 };
    enum class HOME_MENU_OPTIONS
    {
        SinglePlayer, AgainstComputer, Stats, Quit
    };
    const HOME_MENU_OPTIONS HOME_MENU_OPTIONS_ARRAY[] { HOME_MENU_OPTIONS::SinglePlayer,
                                                        HOME_MENU_OPTIONS::AgainstComputer,
                                                        HOME_MENU_OPTIONS::Stats,
                                                        HOME_MENU_OPTIONS::Quit};
    char* ToString(HOME_MENU_OPTIONS homeMenuOptions);
}