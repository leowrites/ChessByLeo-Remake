//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once

#include <array>
#include "entity/piece/Piece.h"
#include "texture/asset.h"
#include "utility/utility.h"
#include "unordered_set"

namespace Chess
{
    using BoardMatrix = std::array<std::array<std::shared_ptr<Piece>, 8>, 8>;
    class Board {
    private:
        BoardMatrix m_board { nullptr };
        std::shared_ptr<Piece> m_whiteKing;
        std::shared_ptr<Piece> m_blackKing;
        std::unordered_set<std::shared_ptr<Piece>> m_whiteRooks;
        std::unordered_set<std::shared_ptr<Piece>> m_blackRooks;
        std::unordered_set<std::shared_ptr<Piece>> m_whiteBishop;
        std::unordered_set<std::shared_ptr<Piece>> m_blackBishop;
        std::unordered_set<std::shared_ptr<Piece>> m_whiteQueen;
        std::unordered_set<std::shared_ptr<Piece>> m_blackQueen;
        void InitializeChessPieces(PlayerRole playerRole);
    public:
        Board();
        BoardMatrix GetBoardMatrix() { return m_board; };
        const std::shared_ptr<Piece>& GetWhiteKing() { return m_whiteKing; };
        const std::shared_ptr<Piece>& GetBlackKing() { return m_blackKing; };
        const std::unordered_set<std::shared_ptr<Piece>>& GetWhiteRooks() { return m_whiteRooks; }
        const std::unordered_set<std::shared_ptr<Piece>>& GetBlackRooks() { return m_blackRooks; }
        const std::unordered_set<std::shared_ptr<Piece>>& GetWhiteBishop() const { return m_whiteBishop; }
        const std::unordered_set<std::shared_ptr<Piece>>& GetBlackBishop() { return m_blackBishop; }
        const std::unordered_set<std::shared_ptr<Piece>>& GetWhiteQueen() { return m_whiteQueen; }
        const std::unordered_set<std::shared_ptr<Piece>>& GetBlackQueen() { return m_blackQueen; }

        void UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, GridPosPtr& newPos, GridPosPtr& oldPos);
    };
}