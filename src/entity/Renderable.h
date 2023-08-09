//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once

#include "cmake-build-debug/_deps/raylib-src/src/raylib.h"

class Renderable {
public:
    virtual Image& getRenderableImage();
};
