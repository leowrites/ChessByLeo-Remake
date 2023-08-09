//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once

#include <iostream>
#include <array>
#include "src/entity/Renderable.h"
#include "SystemManager.h"

namespace Chess
{

    class RenderSystem {
    private:
        std::array<Renderable, MAX_ENTITY> m_renderableEntities{};

    public:
        RenderSystem() = default;
        void Render();
    };
}
