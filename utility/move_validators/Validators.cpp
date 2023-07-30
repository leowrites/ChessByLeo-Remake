//
// Created by Siqi Liu on 2023-07-29.
//

#include "Validators.h"

namespace Chess
{
    std::unique_ptr<MoveValidator> GetValidatorByChessPieceType(ChessPieceType pieceType)
    {
        switch (pieceType)
        {
            case ChessPieceType::pawn:
                return std::make_unique<PawnMoveValidator>( PawnMoveValidator{} );
            case ChessPieceType::rook:
                return nullptr;
                break;
            case ChessPieceType::bishop:
                return nullptr;
                break;
            case ChessPieceType::queen:
                return nullptr;
                break;
            case ChessPieceType::king:
                return nullptr;
                break;
            case ChessPieceType::knight:
                return std::make_unique<KnightMoveValidator>( KnightMoveValidator{} );
                break;
            default:
                return nullptr;
                break;
        }
    }
}