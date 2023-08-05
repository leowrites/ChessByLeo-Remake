//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include <string_view>
#include "utility/utility.h"

namespace Chess {
    class Piece {
    private:
        const ChessPieceType m_chessPieceType;
        const PlayerRole m_pieceOwner;
        // king only
        bool m_isKingInCheck;
        bool m_isAlive { true };
        std::unique_ptr<Vector2> m_oldPosition;
        std::unique_ptr<Vector2> m_chessPosition;
        std::shared_ptr<Texture> m_chessUnselected;
        std::shared_ptr<Texture> m_chessSelected;
        std::unique_ptr<Texture> m_inCheckTexture;
    public:
        Piece(ChessPieceType chessPieceType,
              PlayerRole playerRole,
              const std::string_view& unselectedPath,
              const std::string_view& selectedPath,
              Vector2& initialPosition
              );
        Piece(ChessPieceType chessPieceType,
              PlayerRole playerRole,
              const std::string_view& unselectedPath,
              const std::string_view& selectedPath,
              Vector2& initialPosition,
              const std::string_view& inCheckTexturePath
        );
        static std::shared_ptr<Texture> LoadTextureFromString(std::string_view);
        std::shared_ptr<Texture> GetUnselectedTexture() { return m_chessUnselected; };
        std::shared_ptr<Texture> GetSelectedTexture() { return m_chessSelected; };
        std::unique_ptr<Texture>& GetInCheckTexture() { return m_inCheckTexture; };
        // this will be used to get the piece's original position, and if it's different to current it will be used
        // to remove the original pointer
        std::unique_ptr<Vector2>& GetOldPosition() { return m_oldPosition; };
        std::unique_ptr<Vector2>& GetPosition() { return m_chessPosition; };
        PlayerRole GetPieceOwner() { return m_pieceOwner; };
        ChessPieceType GetPieceType() { return m_chessPieceType; };
        std::string_view GetPieceName() { return ""; };
        bool& GetInCheck() { return m_isKingInCheck; };
        void UpdateInCheck(bool isKingInCheck) { m_isKingInCheck = isKingInCheck; };
        void UpdatePosition(float x, float y);
        void UpdateOldPosition(float x, float y);
        void UpdateIsAlive(bool isAlive) { m_isAlive = isAlive; };
        bool& GetIsAlive() { return m_isAlive; };
        ~Piece() = default;
    };
}
