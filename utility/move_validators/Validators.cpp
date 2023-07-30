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
                break;
            case ChessPieceType::bishop:
                break;
            case ChessPieceType::queen:
                break;
            case ChessPieceType::king:
                break;
            case ChessPieceType::knight:
                break;
        }
    }
}