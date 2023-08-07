//
// Created by Siqi Liu on 2023-07-29.
//

#include "PawnMoveValidator.h"

namespace Chess
{
    std::unique_ptr<std::vector<GridPosPtr>> PawnMoveValidator::GetPossibleMoves(GridPosPtr& start, PlayerRole playerRole, BoardMatrix& board)
    {
        std::unique_ptr<std::vector<GridPosPtr>> possibleMove { std::make_unique<std::vector<GridPosPtr>>() };
        uint8_t& x { start->first };
        uint8_t& y { start->second };
        bool isPlayerWhite { playerRole == PlayerRole::White };
        int direction { isPlayerWhite ? -1 : 1 };
        if (!board[y + direction][x])
        {
            possibleMove->push_back(std::make_unique<GridPos>(x, y + direction));
            if (!board[y + direction * 2][x] && 
            ((isPlayerWhite && y + direction * 2 >= 0 && start->second == 6) || (!isPlayerWhite && y + direction * 2 < 8 && start->second == 1)))
                possibleMove->push_back(std::make_unique<GridPos>(x, y + direction * 2));
        }
        auto enemyOnDiagonal = [&board, &playerRole](GridPos&& grid) {
            return board[grid.second][grid.first] && board[grid.second][grid.first]->GetPieceOwner() != playerRole;
        };
        if (0 <= x - 1 && x - 1 < 8 && 0 <= y + direction && y + direction < 8 && enemyOnDiagonal(GridPos{x - 1, y + direction}))
            possibleMove->push_back(std::make_unique<GridPos>(x - 1, y + direction));
        if (0 <= x + 1 && x + 1 < 8 && 0 <= y + direction && y + direction < 8 && enemyOnDiagonal(GridPos{x + 1, y + direction}))
            possibleMove->push_back(std::make_unique<GridPos>(x + 1, y + direction));
        return possibleMove;
    }
    bool PawnMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board& board) {
        std::unique_ptr<std::vector<GridPosPtr>> possibleMoves { GetPossibleMoves(start, playerRole, board.GetBoardMatrix()) };
        auto posMatch = [&](GridPosPtr& pos) {
            return pos->first == end->first && pos->second == end->second;
        };
        if (auto it = std::find_if(possibleMoves->begin(), possibleMoves->end(), posMatch); it != possibleMoves->end())
            return true;
        return false;
    }
}
