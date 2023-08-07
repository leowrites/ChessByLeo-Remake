//
// Created by Siqi Liu on 2023-07-14.
//

#pragma once

#include <array>
#include "entity/piece/Piece.h"
#include "texture/asset.h"
#include "utility/utility.h"
#include "unordered_set"
#include <map>

namespace Chess
{
    using BoardMatrix = std::array<std::array<std::shared_ptr<Piece>, 8>, 8>;
    using PlayerPieces = std::map<ChessPieceType, std::unordered_set<std::shared_ptr<Piece>>>;
    class Board {
    private:
        BoardMatrix m_board { nullptr };
        std::shared_ptr<Piece> m_whiteKing;
        std::shared_ptr<Piece> m_blackKing;
        std::map<ChessPieceType, std::unordered_set<std::shared_ptr<Piece>>> m_whitePieces;
        std::map<ChessPieceType, std::unordered_set<std::shared_ptr<Piece>>> m_blackPieces;
        void InitializeChessPieces(PlayerRole playerRole);
    public:
        Board();
        BoardMatrix& GetBoardMatrix() { return m_board; };
        const std::shared_ptr<Piece>& GetWhiteKing() { return m_whiteKing; };
        const std::shared_ptr<Piece>& GetBlackKing() { return m_blackKing; };
        PlayerPieces& GetWhitePieces() { return m_whitePieces; };
        PlayerPieces& GetBlackPieces() { return m_blackPieces; };
        void InsertPieceIntoPieces(const std::shared_ptr<Piece>& piece);
        void UpdatePiecePositionInBoard(std::shared_ptr<Piece>& piece, GridPosPtr& newPos, GridPosPtr& oldPos);
        friend ostream& operator<<(ostream& out, Board& board);
    };
}