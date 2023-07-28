//
// Created by Siqi Liu on 2023-07-27.
//

#include "InGameView.h"

namespace Chess
{
    void InGameView::Update() {

    }

    void InGameView::Render(int screenWidth, int screenHeight, std::shared_ptr<Game> &game) {
        Board& board = game->GetBoard();
        for (uint8_t i { 0 }; i < 8; ++i)
        {
            for (uint8_t j { 0 }; j < 8; ++j)
            {
                // render square
                DrawSquare(screenWidth, screenHeight, i, j);
            }
        }
        for (uint8_t i { 0 }; i < 8; ++i)
        {
            for (uint8_t j { 0 }; j < 8; ++j)
            {
                Piece* piece { board.GetBoardMatrix().at(i).at(j).get() };
                // render square
                DrawPiece(screenWidth, screenHeight, i, j, piece);
            }
        }

    }

    void InGameView::DrawSquare(int screenWidth, int screenHeight, uint8_t row, uint8_t col)
    {
        // start from top left (0, 0), calculate the rectangle boxes
        // pixel per square: screenWidth / 8
        // x: pixel per square * col
        // y: pixel per square * row
        // width = height = pixel per square
        auto screenWidthFloat = static_cast<float>(screenWidth);
        float pixelPerSquare = screenWidthFloat / 8;
        Rectangle square = { pixelPerSquare * row, pixelPerSquare * col, screenWidthFloat, screenWidthFloat};
        if ((row + col) % 2 == 0) {
            DrawRectangleRec(square, BOARD_LIGHT_TILE);
        } else {
            DrawRectangleRec(square, BOARD_DARK_TILE);
        }
    }

    void InGameView::DrawPiece(int screenWidth, int screenHeight, uint8_t row, uint8_t col, Piece *piece) {
        if (piece)
        {
            Vector2 pos = { static_cast<float>(100 * row), static_cast<float>(100 * col) };
            DrawTextureEx(*(piece->GetTexture()), pos, 0.0f, 0.45f, WHITE);
        }
    }
}