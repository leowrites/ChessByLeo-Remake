//
// Created by Siqi Liu on 2023-07-13.
//

#include "Piece.h"
#include <iostream>
#include <filesystem>

namespace Chess
{
    Piece::Piece(ChessPieceType chessPieceType, PlayerRole playerRole, const std::string_view imagePath):
    m_chessPieceType(chessPieceType), m_pieceOwner(playerRole)
    {
        std::cout << std::filesystem::current_path();
        m_chessImage = LoadTextureFromString(imagePath);
    }

    std::shared_ptr<Texture> Piece::LoadTextureFromString(const std::string_view imagePath) {
        return std::make_shared<Texture>(LoadTexture(imagePath.data()));
    }
}