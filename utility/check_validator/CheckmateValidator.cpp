//
// Created by Siqi Liu on 2023-07-31.
//

#include "CheckmateValidator.h"

namespace Chess
{
    // take in the king position and the board
    // king is checkmate if
    // 1. king has nowhere to move
    // 2. (if is being checked vertically/horizontally/diagonally) no piece can move between
    // 3. no piece can take the attacker
    bool CheckmateValidator::IsCheckmate(const std::shared_ptr<Piece>& king, Board &board) {
        GridPosPtr kingPos { std::move(CalculateGridPosGivenCoord(king->GetPosition()) )};
        std::array possibleKingPos {
                GridPos {kingPos->first - 1, kingPos->second + 1},
                GridPos {kingPos->first + 1, kingPos->second + 1},
                GridPos {kingPos->first - 1, kingPos->second - 1},
                GridPos {kingPos->first + 1, kingPos->second - 1},
                GridPos {kingPos->first, kingPos->second + 1},
                GridPos {kingPos->first, kingPos->second - 1},
                GridPos {kingPos->first - 1, kingPos->second},
                GridPos {kingPos->first + 1, kingPos->second}
        };
        // return true if king can move to pos and still not be in check, false otherwise
        auto canKingMove{[&](const GridPos &pos) {
            if (pos.first > 7 || pos.first < 0 || pos.second > 7 || pos.second < 0)
                return false;
            std::shared_ptr<Piece> tempDestPiece { board.GetBoardMatrix()[pos.second][pos.first] };
            if (tempDestPiece && tempDestPiece->GetPieceOwner() == king->GetPieceOwner())
                return false;
            std::shared_ptr<Piece> kingPiece { board.GetBoardMatrix()[kingPos->second][kingPos->first] };

            GridPosPtr oldPos { std::move(CalculateGridPosGivenCoord(kingPiece->GetPosition())) };
            GridPosPtr newPos { std::make_unique<GridPos>(pos) };

            FakeMoveToNewPos(oldPos, newPos, board);
            bool canKingMoveToGrid { true };
            if (IsKingInCheck(king->GetPieceOwner(), board))
                canKingMoveToGrid = false;
            FakeMoveFromNewPos(oldPos, newPos, board);
            return canKingMoveToGrid;
        }};
        if (std::any_of(possibleKingPos.begin(), possibleKingPos.end(), canKingMove))
            return true;
        // brute force
        // for all pieces owned by the current player, move it to all possible positions (test capture and blocking)
        PlayerPieces& pieces { king->GetPieceOwner() == PlayerRole::White ? board.GetWhitePieces() : board.GetBlackPieces() };
        for (auto& [key, values]: pieces)
        {
            // for each piece, try all possible moves
            // fake move to new pos call isKinginCheck then move back
            for (auto& value: values)
            {
                std::unique_ptr<std::vector<GridPosPtr>> pos { std::move(board.GetAllPossiblePositionsForPiece(value)) };
            }
        }
        return false;
    }
    void CheckmateValidator::FakeMoveToNewPos(GridPosPtr& oldPos, GridPosPtr& newPos, Board& board)
    {
        BoardMatrix& boardMatrix { board.GetBoardMatrix() };
        if (!boardMatrix[oldPos->second][oldPos->first])
            return;
        std::shared_ptr<Piece>& oldPosPiece { boardMatrix[oldPos->second][oldPos->first] };
        std::shared_ptr<Piece>& newPosPiece { boardMatrix[newPos->second][newPos->first] };
        oldPosPiece->UpdatePosition(newPos->first * 100, newPos->second * 100);
        if (newPosPiece)
            newPosPiece->UpdateIsAlive(false);
        m_movedPiece = newPosPiece;
        board.UpdatePiecePositionInBoard(oldPosPiece, newPos, oldPos);
    };
    void CheckmateValidator::FakeMoveFromNewPos(GridPosPtr& oldPos, GridPosPtr& newPos, Board& board)
    {
        BoardMatrix& boardMatrix { board.GetBoardMatrix() };
        std::shared_ptr<Piece>& piece { boardMatrix[newPos->second][newPos->first] };
        // move from oldPos to newPos again
        piece->UpdatePosition(oldPos->first * 100, oldPos->second * 100);
        board.UpdatePiecePositionInBoard(piece, oldPos, newPos);
        board.GetBoardMatrix()[newPos->second][newPos->first] = m_movedPiece;
        if (m_movedPiece)
            m_movedPiece->UpdateIsAlive(true);
    };
}

