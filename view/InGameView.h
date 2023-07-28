//
// Created by Siqi Liu on 2023-07-27.
//

#pragma once

#include <iostream>
#include "entity/Game.h"
#include "utility/utility.h"


namespace Chess
{
    class InGameView
    {
    public:
        static void Render(int screenWidth, int screenHeight, std::shared_ptr<Game>& game);
        static void Update();
    private:
        static void DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col);
        static void DrawPiece(int screenWidth, int screenHeight, uint8_t row, uint8_t col, Piece *piece);
    };
}