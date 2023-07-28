//
// Created by Siqi Liu on 2023-07-17.
//

#include <iostream>
#include <sstream>
#include "raygui.h"
#include "GameConfigView.h"
#include "utility/utility.h"

namespace Chess
{
    int GameConfigView::s_selectedComputerDifficulty {0 };
    bool GameConfigView::s_showDifficultyDropdownBox {false };
    int GameConfigView::s_selectedGameTime { 0 };
    bool GameConfigView::s_showGameTimeDropBox { false };
    const std::string_view GameConfigView::s_gameTimeOptions { "03:00 MINUTES;05:00 MINUTES;10:00 MINUTES" };
    bool GameConfigView::s_clickedNext { false };
    void GameConfigView::Render()
    {
        const int textWidth { MeasureText(computerDifficultyString.data(), HOME_MENU_TEXT_FONT_SIZE) };
        const Rectangle difficultyDropdown {SCREEN_PADDING_X,
                                      SCREEN_PADDING_Y,
                                      static_cast<float>(textWidth),
                                      HOME_MENU_TEXT_FONT_SIZE};

        int difficultyClick { GuiDropdownBox(difficultyDropdown, computerDifficultyString.data(),
                                             &s_selectedComputerDifficulty, s_showDifficultyDropdownBox) };
        if (difficultyClick)
            s_showDifficultyDropdownBox = !s_showDifficultyDropdownBox;

        const std::string_view gameTimeText { s_gameTimeOptions };
//        const int gameTimeTextWidth { MeasureText(gameTimeText.data(), HOME_MENU_TEXT_FONT_SIZE) };
        const Rectangle gameTimeDropdown {
                SCREEN_PADDING_X,
                SCREEN_PADDING_Y + HOME_MENU_TEXT_FONT_SIZE * 5,
                static_cast<float>(textWidth),
                HOME_MENU_TEXT_FONT_SIZE
        };
        int gameTimeClick { GuiDropdownBox(gameTimeDropdown, gameTimeText.data(),
                                             &s_selectedGameTime, s_showGameTimeDropBox) };
        if (gameTimeClick)
            s_showGameTimeDropBox = !s_showGameTimeDropBox;

        Rectangle nextButton { gameTimeDropdown };
        nextButton.y = nextButton.y + + HOME_MENU_TEXT_FONT_SIZE * 5;
        // next button
        s_clickedNext = GuiButton(nextButton, "Next");
    }

    void GameConfigView::Update(Vector2& mousePosition, GameConfiguration& gameConfiguration, GameState& gameState)
    {
        const ComputerDifficulty castedDifficulty { static_cast<ComputerDifficulty>(s_selectedComputerDifficulty) };
        if (castedDifficulty != gameConfiguration.GetDifficulty())
        {
            gameConfiguration.UpdateSelectedDifficulty(castedDifficulty);
        }
        if (s_clickedNext)
        {
            gameState = GameState::Loading;
        }
    }

    void GameConfigView::Reset() {

    }
}