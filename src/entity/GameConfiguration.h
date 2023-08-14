//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once
#include <string_view>
#include <ctime>

namespace Chess
{
    enum class ComputerDifficulty
    {
        Easy, Medium, Difficult
    };
    const std::string_view computerDifficultyString{ "Easy;Medium;Difficult" };
    class GameConfiguration {
    private:
        const char* m_time_format{ "%M:%S" };
        std::tm m_gameTime {};
        ComputerDifficulty m_difficulty;

    public:
        GameConfiguration();
        ComputerDifficulty GetDifficulty() { return m_difficulty; };
        void UpdateSelectedDifficulty(ComputerDifficulty difficulty);
        void UpdateGameTime(std::stringstream ss);
        void Reset();
    };
}
