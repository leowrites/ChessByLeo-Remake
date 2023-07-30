//
// Created by Siqi Liu on 2023-07-29.
//

#include "PawnMoveValidator.h"

namespace Chess
{
    bool Chess::PawnMoveValidator::AbovePieceExists(Chess::GridPosPtr &end, Chess::Board &board)
    {
        if (board.GetBoardMatrix()[end->second][end->first])
            return true;
        return false;
    }
    bool Chess::PawnMoveValidator::DiagonalEnemyExists(Chess::GridPosPtr &end, Chess::PlayerRole playerRole,
                                                       Chess::Board &board)
    {
        // player role is the role of the current player
        // assume the end is valid for the current player (i.e. end is white piece moving up in a valid location)
        std::shared_ptr<Piece> piece { board.GetBoardMatrix()[end->second][end->first] };
        if (piece && piece->GetPieceOwner() != playerRole)
            return true;
        return false;
    }
    bool Chess::PawnMoveValidator::validate(GridPosPtr &start, GridPosPtr &end, PlayerRole playerRole, Board& board) {
        // pawn can move one/two step forward if it hasn't been moved, it can move diagonal if there is an enemy piece
        // assume white is always on the bottom
        if (playerRole == PlayerRole::White)
        {
            if (start->second == 6 && ((end->second == 5 || end->second == 4) && end->first == start->first))
            {
                return true;
            }
            else if ((end->first == start->first + 1 && end->second == start->second - 1)
            || (end->first == start->first - 1 && end->second == start->second - 1))
            {
                return DiagonalEnemyExists(end, playerRole, board);
            }
            else if (start->first == end->first && start->second - 1 == end->second)
            {
                return !AbovePieceExists(end, board);
            }
        }
        else
        {
            if (start->second == 1 && ((end->second == 2 || end->second == 3) && end->first == start->first))
            {
                return true;
            }
            else if ((end->first == start->first - 1 && end->second == start->second + 1)
                     || (end->first == start->first + 1 && end->second == start->second + 1))
            {
                return DiagonalEnemyExists(end, playerRole, board);
            }
            else if (start->first == end->first && start->second + 1 == end->second)
            {
                return !AbovePieceExists(end, board);
            }
        }

        return false;
    }
}
