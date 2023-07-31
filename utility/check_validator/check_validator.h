#pragma once

#include <iostream>
#include "utility/utility.h"
#include "entity/Game.h"
#include "entity/board/Board.h"
#include "array"
#include "algorithm"

namespace Chess
{
    // we can call this when
    // 1. before current player makes a move, use it to check if its king wiill be exposed to a check
    // 2. after current player makes a move, use it to check if the other player's king is in check
    // 3. if current player is being checked by the other player, check if the move wish to be performed will
    //      remove the check status for the current player
    bool IsKingInCheck(PlayerRole playerRole, Game& game, Board& board);
}