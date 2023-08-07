//
// Created by Siqi Liu on 2023-07-31.
//

#pragma once

#include "utility/utility.h"
#include "entity/board/Board.h"
#include "utility/check_validator/CheckValidator.h"
#include "utility/move_validators/PawnMoveValidator.h"
namespace Chess {
    class CheckmateValidator
    {
    private:
        std::shared_ptr<Piece> m_movedPiece;
        // functions that can be used to make a temporary move
        void FakeMoveToNewPos(GridPosPtr& oldPos, GridPosPtr& newPos, Board& board);
        void FakeMoveFromNewPos(GridPosPtr& oldPos, GridPosPtr& newPos, Board& board);
        static std::unique_ptr<std::vector<GridPosPtr>> GetAllPossiblePositionsForPiece(const std::shared_ptr<Piece> &piece, BoardMatrix& board);
        static std::unique_ptr<std::vector<GridPosPtr>> GetAllPossibleHorizontalAndVerticalPositions(const std::shared_ptr<Piece> &piece, BoardMatrix& board);
        static std::unique_ptr<std::vector<GridPosPtr>> GetAllPossibleDiagonalPositions(const std::shared_ptr<Piece> &piece, BoardMatrix& board);
    public:
        CheckmateValidator() = default;
        bool IsCheckmate(const std::shared_ptr<Piece>& king, Board &board);
    };
}
