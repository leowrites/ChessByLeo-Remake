//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include "../player/Player.h"
#include <string_view>

namespace Chess {
    using Position = std::pair<int, int>;
    enum class ChessPieceType {
        pawn, rook, bishop, queen, king, knight
    };

    enum class PlayerRole;

    class Piece {
    private:
        const ChessPieceType m_chessPieceType;
        const PlayerRole m_pieceOwner;
        const std::string_view m_pathToSprite;
        Position m_chessPosition;
        std::shared_ptr<Texture> m_chessImage;
    protected:
        Piece(ChessPieceType chessPieceType, PlayerRole playerRole, std::string_view imagePath);
    public:
        virtual void Render() = 0;
        static std::shared_ptr<Texture> LoadTextureFromString(std::string_view);
        std::shared_ptr<Texture> GetTexture() { return m_chessImage; };
        virtual std::string_view GetPieceName() = 0;
        virtual ~Piece() = default;
    };
}
