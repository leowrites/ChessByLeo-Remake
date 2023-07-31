//
// Created by Siqi Liu on 2023-07-13.
//

#include "Piece.h"
#include <iostream>
#include <filesystem>

namespace Chess
{
    Piece::Piece(ChessPieceType chessPieceType,
                 PlayerRole playerRole,
                 const std::string_view& unselectedPath,
                 const std::string_view& selectedPath, Vector2& initialPosition
                 ):
    m_chessPieceType(chessPieceType), m_pieceOwner(playerRole)
    {
        // pieces may share validators so use shared_ptr
        std::cout << std::filesystem::current_path();
        m_chessUnselected = LoadTextureFromString(unselectedPath);
        m_chessSelected = LoadTextureFromString(selectedPath);
        m_chessPosition = std::make_unique<Vector2>(initialPosition);
        m_oldPosition = std::make_unique<Vector2>(initialPosition);
    }

    std::shared_ptr<Texture> Piece::LoadTextureFromString(const std::string_view imagePath) {
        return std::make_shared<Texture>(LoadTexture(imagePath.data()));
    }

    void Piece::UpdatePosition(float x, float y) {
        m_chessPosition->x = x;
        m_chessPosition->y = y;
    }

    void Piece::UpdateOldPosition(float x, float y) {
        m_oldPosition->x = x;
        m_oldPosition->y = y;
    }

    Piece::Piece(ChessPieceType chessPieceType,
                 PlayerRole playerRole,
                 const std::string_view &unselectedPath,
                 const std::string_view &selectedPath,
                 Vector2 &initialPosition,
                 const std::string_view &inCheckTexturePath)
                 :Piece(chessPieceType, playerRole, unselectedPath, selectedPath, initialPosition)
    {
        m_inCheckTexture = std::move(std::make_unique<Texture>( LoadTexture(inCheckTexturePath.data())));
    }
}