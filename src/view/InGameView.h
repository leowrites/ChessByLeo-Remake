//
// Created by Siqi Liu on 2023-07-27.
//

#pragma once

#include <iostream>
#include "src/entity/Game.h"
#include "src/utility/utility.h"
#include "src/utility/move_validators/Validators.h"
#include "src/utility/check_validator/CheckValidator.h"
#include "src/utility/check_validator/CheckmateValidator.h"

namespace Chess
{
    class InGameView
    {
    public:
        static void Render(int screenWidth, int screenHeight, std::shared_ptr<Game>& game);
        static void Update(const std::shared_ptr<Game>& game, GameState& currGameState);
    private:
        static bool gameOver;
        static void DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col);
        static void DrawPiece(int screenWidth, int screenHeight, Piece *piece, const std::shared_ptr<Game>& game);
        static void DrawWinText(int screenWidth=800, int screenHeight=800);
    };
}