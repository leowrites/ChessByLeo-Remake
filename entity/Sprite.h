//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once
#include <iostream>
#include "raylib.h"

namespace Sprite {
    // should not have more than 100 assets loaded at once
    const std::uint8_t MAX_SPRITE { 100 };
    class Sprite {
    private:
        Image m_image;
    };
}
