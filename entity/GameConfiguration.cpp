//
// Created by Siqi Liu on 2023-07-14.
//

#include <sstream>
#include <iomanip>
#include "GameConfiguration.h"

namespace Chess
{
    void GameConfiguration::Reset() {
        std::stringstream ss("03:00");
        ss >> std::get_time(&m_gameTime, m_time_format);
        m_difficulty = ComputerDifficulty::Easy;
    }

    void GameConfiguration::UpdateSelectedDifficulty(ComputerDifficulty difficulty) {
        m_difficulty = difficulty;
    }

    void GameConfiguration::UpdateGameTime(std::stringstream ss) {
        ss >> std::get_time(&m_gameTime, m_time_format);
    }

    GameConfiguration::GameConfiguration() {
        m_difficulty = ComputerDifficulty::Easy;
    }
}