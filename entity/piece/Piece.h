//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include "../player/Player.h"
#include <string_view>

namespace Chess {
    enum class ChessPieceType {
        pawn, rook, bishop, queen, king, knight
    };

    enum class PlayerRole;

    class Piece {
    private:
        const ChessPieceType m_chessPieceType;
        const PlayerRole m_pieceOwner;
        const std::string_view m_pathToSprite;
        std::unique_ptr<Vector2> m_chessPosition;
        std::shared_ptr<Texture> m_chessUnselected;
        std::shared_ptr<Texture> m_chessSelected;
    protected:
        Piece(ChessPieceType chessPieceType, PlayerRole playerRole, const std::string_view& unselectedPath,
              const std::string_view& selectedPath, Vector2& initialPosition);
    public:
        virtual void Render() = 0;
        static std::shared_ptr<Texture> LoadTextureFromString(std::string_view);
        std::shared_ptr<Texture> GetUnselectedTexture() { return m_chessUnselected; };
        std::shared_ptr<Texture> GetSelectedTexture() { return m_chessSelected; };
        std::unique_ptr<Vector2>& GetPosition() { return m_chessPosition; };
        void UpdatePosition(float x, float y);
        virtual std::string_view GetPieceName() = 0;
        virtual ~Piece() = default;
    };
}
