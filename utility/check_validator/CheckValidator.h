#pragma once

#include <iostream>
#include "utility/utility.h"
#include "entity/Game.h"
#include "entity/board/Board.h"
#include "array"
#include "algorithm"
#include "unordered_set"
#include "utility/move_validators/ValidatorHelper.h"

namespace Chess
{
    // we can call this when
    // 1. before current player makes a move, use it to check if its king wiill be exposed to a check
    // 2. after current player makes a move, use it to check if the other player's king is in check
    // 3. if current player is being checked by the other player, check if the move wish to be performed will
    //      remove the check status for the current player
    bool IsKingInCheck(PlayerRole playerRole, Game& game, Board& board);
    bool IsKingInCheckByPawn(PlayerRole playerRole, GridPosPtr &kingPos, Board &board);
    bool IsKingInCheckByRook(PlayerRole playerRole, GridPosPtr &kingPos, Board &board);
    bool IsKingInCheckByQueen(PlayerRole playerRole, GridPosPtr &kingPos, Board &board);
    bool IsKingInCheckByBishop(PlayerRole playerRole, GridPosPtr &kingPos, Board &board);
    bool IsKingInCheckByKnight(PlayerRole playerRole, GridPosPtr &kingPos, Board& board);
    bool IsKingInCheckHorizontal(GridPosPtr &kingPos, Board& board, const std::shared_ptr<Piece>& pieces);
    bool IsKingInCheckVertical(GridPosPtr &kingPos, Board& board, const std::shared_ptr<Piece>& pieces);
    bool IsKingInCheckDiagonal(GridPosPtr &kingPos, Board& board, const std::shared_ptr<Piece>& pieces);
}