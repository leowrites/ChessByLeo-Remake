//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once

#include <array>
#include "entity/piece/Piece.h"
#include "texture/asset.h"
#include "utility/utility.h"

namespace Chess
{
    using BoardMatrix = std::array<std::array<std::shared_ptr<Piece>, 8>, 8>;
    class Board {
    private:
        BoardMatrix m_board { nullptr };
        void InitializeChessPieces(PlayerRole playerRole);
    public:
        Board();
        BoardMatrix GetBoardMatrix() { return m_board; };
        void UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, GridPosPtr& newPos, GridPosPtr& oldPos);
    };
}