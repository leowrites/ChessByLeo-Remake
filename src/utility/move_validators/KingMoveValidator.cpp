//
// Created by Siqi Liu on 2023-07-29.
//

#include "KingMoveValidator.h"

namespace Chess
{
    bool KingMoveValidator::validate(Chess::GridPosPtr &start, Chess::GridPosPtr &end, Chess::PlayerRole playerRole,
                                     Chess::Board &board)
    {
        std::array possiblePos {
                GridPos {start->first - 1, start->second + 1},
                GridPos {start->first + 1, start->second + 1},
                GridPos {start->first - 1, start->second - 1},
                GridPos {start->first + 1, start->second - 1},
                GridPos {start->first, start->second + 1},
                GridPos {start->first, start->second - 1},
                GridPos {start->first - 1, start->second},
                GridPos {start->first + 1, start->second}
        };
        GridPos endPos { *end.get() };
        auto isSameGrid = [endPos](GridPos pos)
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