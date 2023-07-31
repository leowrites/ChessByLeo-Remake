//
// Created by Siqi Liu on 2023-07-27.
//

#pragma once

#include <iostream>
#include "entity/Game.h"
#include "utility/utility.h"
#include "utility/move_validators/Validators.h"
#include "utility/check_validator/check_validator.h"

namespace Chess
{
    class InGameView
    {
    public:
        static void Render(int screenWidth, int screenHeight, std::shared_ptr<Game>& game);
        static void Update(const std::shared_ptr<Game>& game);
    private:
        static void DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col);
        static void DrawPiece(int screenWidth, int screenHeight, Piece *piece, const std::shared_ptr<Game>& game);
    };
}