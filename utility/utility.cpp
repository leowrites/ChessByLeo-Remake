//
// Created by Siqi Liu on 2023-07-17.
//

#include "utility.h"

namespace Chess
{
    char* ToString(HOME_MENU_OPTIONS homeMenuOptions)
    {
        const char* MENU_OPTIONS[] { "Single Player", "Against Computer", "Stats", "Quit" };
        return const_cast<char *>(MENU_OPTIONS[static_cast<int>(homeMenuOptions)]);
    }
}