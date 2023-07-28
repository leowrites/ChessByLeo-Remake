//
// Created by Siqi Liu on 2023-07-17.
//

#include "LoadingView.h"
#include "utility/utility.h"

namespace Chess
{
    void LoadingView::Render(int screenWidth, int screenHeight) {
        const char* title { "Loading..."};
        const int titleWidth {MeasureText(title, TITLE_TEXT_FONT_SIZE) };
        const int alignedX { (screenWidth - titleWidth) / 2 };
        DrawText(title,
                 alignedX,
                 (screenHeight - TITLE_TEXT_FONT_SIZE) / 3,
                 TITLE_TEXT_FONT_SIZE,
                 MAROON);
    }



    void LoadingView::InitializeGame(std::shared_ptr<Chess::Game>& gamePtr, GameConfiguration &gameConfiguration) {
        if (!gamePtr)
        {
            gamePtr = std::make_shared<Game>(gameConfiguration);
        }

    }

    void LoadingView::Update(GameState &gameState) {
        gameState = GameState::InGame;
    }
}
