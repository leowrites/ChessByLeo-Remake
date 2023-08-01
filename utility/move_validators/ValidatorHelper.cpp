//
// Created by Siqi Liu on 2023-07-29.
//

#include "ValidatorHelper.h"

namespace Chess
{
    bool DestinationIsEnemyOrEmpty(GridPosPtr& end, PlayerRole player, Board& board)
    {
        if (!board.GetBoardMatrix()[end->second][end->first])
            return true;
        if (board.GetBoardMatrix()[end->second][end->first]->GetPieceOwner() != player)
            return true;
        return false;
    }
    bool ValidateHorizontal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board)
    {
        // check if there are pieces between start and end horizontally
        // return true if there are no piece in between AND last square is enemy or empty
        if (start->second != end->second)
            return false;
        if (PieceInBetweenHorizontal(start, end, board))
            return false;
        // check destination piece is not from the same player
        if (DestinationIsEnemyOrEmpty(end, player, board))
            return true;
        return false;
    }
    bool ValidateVertical(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board)
    {
        // check if there are pieces between start and end vertically
        if (start->first != end->first)
            return false;
        if (PieceInBetweenVertical(start, end, board))
            return false;
        if (DestinationIsEnemyOrEmpty(end, player, board))
            return true;
        return false;
    }
    bool ValidateDiagonal(GridPosPtr& start, GridPosPtr& end, PlayerRole player, Board& board)
    {
        // the difference for x and y between start and end should be the same
        // then check everything along that line
        int diffX { end->first - start->first };
        int diffY { end->second - start->second};
        if (abs(diffX) != abs(diffY))
            return false;
        if (PieceInBetweenDiagonal(start, end, board, diffX > 0 ? 1 : -1, diffY > 0 ? 1 : -1))
            return false;
        if (DestinationIsEnemyOrEmpty(end, player, board))
            return true;
        return false;
    }
    bool PieceInBetweenHorizontal(GridPosPtr &start, GridPosPtr &end, Board &board)
    {
        // pre condition: start and end are horizontal to each other
        uint8_t minX = min(start->first, end->first) + 1;
        uint8_t maxX = max(start->first, end->first);
        for (uint8_t currX { minX }; currX < maxX; ++currX)
        {
            if (board.GetBoardMatrix()[end->second][currX])
                return true;
        }
        return false;
    }
    bool PieceInBetweenVertical(GridPosPtr &start, GridPosPtr &end, Board &board)
    {
        uint8_t minY = min(start->second, end->second) + 1;
        uint8_t maxY = max(start->second, end->second);
        // check from start to end (not inclusive), if there are pieces in between
        for (uint8_t currY { minY }; currY < maxY; ++currY)
        {
            if (board.GetBoardMatrix()[currY][end->first])
                return true;
        }
        return false;
    }
    bool PieceInBetweenDiagonal(GridPosPtr &start, GridPosPtr &end, Board &board, int8_t xDir, int8_t yDir)
    {
        // if the same, use start->first as index, increment/decrement both x and y until the same and check every square on the board
        uint8_t currX { start->first };
        uint8_t currY { start->second };
        while (currX != end->first && currY != end->second)
        {
            // don't check the last time
            currX += xDir;
            currY += yDir;
            if (currX == end->first && currY == end->second)
                break;
            if (board.GetBoardMatrix()[currY][currX])
                return true;
        }
        return false;
    };
}
