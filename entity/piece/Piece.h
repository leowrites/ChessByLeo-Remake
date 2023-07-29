//
// Created by Siqi Liu on 2023-07-13.
//

#pragma once
#include <iostream>
#include <raylib.h>
#include "../player/Player.h"
#include <string_view>
//#include "utility/move_validators/Validators.h"

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
//        const std::shared_ptr<MoveValidator> m_validator;
        std::unique_ptr<Vector2> m_oldPosition;
        std::unique_ptr<Vector2> m_chessPosition;
        std::shared_ptr<Texture> m_chessUnselected;
        std::shared_ptr<Texture> m_chessSelected;
    protected:
        Piece(ChessPieceType chessPieceType,
              PlayerRole playerRole,
              const std::string_view& unselectedPath,
              const std::string_view& selectedPath, Vector2& initialPosition
//              const std::shared_ptr<MoveValidator>& validator
              );
    public:
        virtual void Render() = 0;
        static std::shared_ptr<Texture> LoadTextureFromString(std::string_view);
        std::shared_ptr<Texture> GetUnselectedTexture() { return m_chessUnselected; };
        std::shared_ptr<Texture> GetSelectedTexture() { return m_chessSelected; };
        // this will be used to get the piece's original position, and if it's different to current it will be used
        // to remove the original pointer
        std::unique_ptr<Vector2>& GetOldPosition() { return m_oldPosition; };
        std::unique_ptr<Vector2>& GetPosition() { return m_chessPosition; };
        void UpdatePosition(float x, float y);
        void UpdateOldPosition(float x, float y);
        virtual std::string_view GetPieceName() = 0;
        virtual ~Piece() = default;
    };
}
