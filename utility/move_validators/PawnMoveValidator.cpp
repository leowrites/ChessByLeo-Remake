//
// Created by Siqi Liu on 2023-07-29.
//

#include "PawnMoveValidator.h"

namespace Chess
{
    bool PawnMoveValidator::AbovePieceExists(GridPosPtr& start, GridPosPtr &end, Board &board)
    {
        const int diffY { end->second - start->second };
        const int dir { diffY > 0 ? 1 : -1 };
        if (abs(diffY) == 1)
            return board.GetBoardMatrix()[start->second + dir][start->first] != nullptr;
        if (abs(diffY) == 2)
            return board.GetBoardMatrix()[start->second + dir][start->first] != nullptr
            || board.GetBoardMatrix()[start->second + dir * 2][start->first] != nullptr;
        return false;
    }
    bool PawnMoveValidator::DiagonalEnemyExists(GridPosPtr &end, PlayerRole playerRole,
                                                       Board &board)
    {
        // player role is the role of the current player
        // assume the end is valid for the current player (i.e. end is white piece moving up in a valid location)
        std::shared_ptr<Piece> piece { board.GetBoardMatrix()[end->second][end->first] };
        if (piece && piece->GetPieceOwner() != playerRole)
            return true;
        return false;
    }
    bool PawnMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board& board) {
        // pawn can move one/two step forward if it hasn't been moved, it can move diagonal if there is an enemy piece
        // assume white is always on the bottom
        if (playerRole == PlayerRole::White)
        {
            if (start->second == 6 && ((end->second == 5 || end->second == 4) && end->first == start->first))
            {
                return !AbovePieceExists(start, end, board);
            }
            else if ((end->first == start->first + 1 && end->second == start->second - 1)
            || (end->first == start->first - 1 && end->second == start->second - 1))
            {
                return DiagonalEnemyExists(end, playerRole, board);
            }
            else if (start->first == end->first && start->second - 1 == end->second)
            {
                return !AbovePieceExists(start, end, board);
            }
        }
        else
        {
            if (start->second == 1 && ((end->second == 2 || end->second == 3) && end->first == start->first))
            {
                return !AbovePieceExists(start, end, board);
            }
            else if ((end->first == start->first - 1 && end->second == start->second + 1)
                     || (end->first == start->first + 1 && end->second == start->second + 1))
            {
                return DiagonalEnemyExists(end, playerRole, board);
            }
            else if (start->first == end->first && start->second + 1 == end->second)
            {
                return !AbovePieceExists(start, end, board);
            }
        }

        return false;
    }
}
