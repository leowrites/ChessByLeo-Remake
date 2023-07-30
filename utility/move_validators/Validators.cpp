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
                return std::make_unique<RookMoveValidator>(RookMoveValidator{} );
            case ChessPieceType::bishop:
                return std::make_unique<BishopMoveValidator> ( BishopMoveValidator{} );
            case ChessPieceType::queen:
                return std::make_unique<QueenMoveValidator> ( QueenMoveValidator{} );
            case ChessPieceType::king:
                return std::make_unique<KingMoveValidator>( KingMoveValidator{} );
            case ChessPieceType::knight:
                return std::make_unique<KnightMoveValidator>( KnightMoveValidator{} );
            default:
                return nullptr;
        }
    }
}