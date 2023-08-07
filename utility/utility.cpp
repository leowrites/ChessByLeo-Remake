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
    GridPosPtr CalculateGridPosGivenCoord(int x, int y)
    {
        return std::make_unique<std::pair<uint8_t, uint8_t>>(
                x / SQUARE_PIXEL_SIZE % 8,
                y / SQUARE_PIXEL_SIZE % 8
                );
    }
    GridPosPtr CalculateGridPosGivenCoord(std::unique_ptr<Vector2>& windowPosition)
    {
        return std::make_unique<GridPos>(
                static_cast<int>(windowPosition->x) / SQUARE_PIXEL_SIZE % 8,
                static_cast<int>(windowPosition->y) / SQUARE_PIXEL_SIZE % 8
                );
    }
}