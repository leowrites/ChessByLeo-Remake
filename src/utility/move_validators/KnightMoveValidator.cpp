//
// Created by Siqi Liu on 2023-07-29.
//

#include "KnightMoveValidator.h"

namespace Chess
{
    std::unique_ptr<std::vector<GridPosPtr>> KnightMoveValidator::GetPossibleMoves(GridPosPtr& start, PlayerRole playerRole, BoardMatrix& board)
    {
        // return valid moves
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
        std::unique_ptr<std::vector<GridPosPtr>> validPos { std::make_unique<std::vector<GridPosPtr>>() };
        for (auto& pos: possiblePos)
        {
            // 1. pos need to be inside the board
            if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7)
                continue;
            // 2. pos need to be empty or enemy (alive or dead)
            if (!board[pos.second][pos.first] || board[pos.second][pos.first]->GetPieceOwner() != playerRole)
                validPos->push_back(std::make_unique<GridPos>(pos.first, pos.second));
        }
        return validPos;

    }
    bool KnightMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board &board)
    {
        std::unique_ptr<std::vector<GridPosPtr>> validPos { std::move(GetPossibleMoves(start, playerRole, board.GetBoardMatrix())) };
        // check if end is in validPos
        auto isSameGrid = [&](GridPosPtr& pos)
        {
            return end->first == pos->first && end->second == pos->second;
        };

        auto pos = std::find_if(std::begin(*validPos), std::end(*validPos), isSameGrid);
        return pos != validPos->end();
    }
}