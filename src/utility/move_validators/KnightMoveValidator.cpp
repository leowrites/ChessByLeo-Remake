//
// Created by Siqi Liu on 2023-07-29.
//

#include "KnightMoveValidator.h"

namespace Chess
{
    bool KnightMoveValidator::validate(Chess::GridPosPtr &start, Chess::GridPosPtr &end, Chess::PlayerRole playerRole,
                                       Chess::Board &board)
    {
        // knight can go up 2 left 1, up 2 right 1, ...
        // if end is any of them, return true
        std::array possiblePos {
                GridPos {start->first - 1, start->second + 2},
                GridPos {start->first + 1, start->second + 2},
                GridPos {start->first - 1, start->second - 2},
                GridPos {start->first + 1, start->second - 2},
                GridPos {start->first - 2, start->second + 1},
                GridPos {start->first + 2, start->second + 1},
                GridPos {start->first - 2, start->second - 1},
                GridPos {start->first + 2, start->second - 1}
        };
        GridPos endPos { *end.get() };
        auto isSameGrid = [endPos](GridPos& pos)
        {
            return endPos.first == pos.first && endPos.second == pos.second;
        };
        GridPos* pos = std::find_if(std::begin(possiblePos), std::end(possiblePos), isSameGrid);
        if (pos == possiblePos.end())
            return false;
        if (!board.GetBoardMatrix()[pos->second][pos->first])
            return true;
        if (board.GetBoardMatrix()[pos->second][pos->first]->GetPieceOwner() != playerRole)
            return true;
        return false;
    }
}