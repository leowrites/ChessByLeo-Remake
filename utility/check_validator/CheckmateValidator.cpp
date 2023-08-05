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
    // brute force:
    // 1. king would have 8 squares around it which it can move to, we can check all 8 to see if king can move
    //     run time: 8 * (# of rooks(2) * 8 + # of bishops(2) * 8 + # of queen * 24 (can optimize down to 8 if we get
    //     direction first) + # of knights(2) * 12 + # of pawns(8) * 2)
    //
    // 2. we can first figure out which direction king is being checked from, then we can go through all pieces
    //      if the piece can be placed in between the attacker and the king
    bool IsCheckmate(const std::shared_ptr<Piece>& king, Board &board) {
        // 1. check that 8 squares around
        //      a. can king move there? it can if the square is occupied by enemy or is empty.
        //      b. if it can, will it be placed in check? we can call IsKingInCheck
        //    if all return false, then king cannot move anywhere
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
        auto canKingMove{[&](const GridPos &pos) {
            if (pos.first > 7 || pos.first < 0 || pos.second > 7 || pos.second < 0)
                return false;
            // if square is occupied by same color, then it cannot move there
            // temporarily move the piece here, and that square will temporarily be nullptr
            std::shared_ptr<Piece> tempDestPiece { board.GetBoardMatrix()[pos.second][pos.first] };
            if (tempDestPiece && tempDestPiece->GetPieceOwner() == king->GetPieceOwner())
                return false;
            // move the tempDestPieceBack

            // Temporarily move king to that position and run isKingInCheck, that square in board will be nullptr
            std::shared_ptr<Piece> kingPiece { board.GetBoardMatrix()[kingPos->second][kingPos->first] };
            GridPosPtr oldPos { std::move(CalculateGridPosGivenCoord(kingPiece->GetPosition())) };
            GridPosPtr newPos { std::make_unique<GridPos>(pos) };
            // move king to the new pos, original will be nullptr
            // need to actually update x y position as well
            kingPiece->UpdatePosition(newPos->first * 100, newPos->second * 100);
            board.UpdatePiecePositionInBoard(kingPiece, newPos, oldPos);
            if (IsKingInCheck(king->GetPieceOwner(), board))
            {
                board.UpdatePiecePositionInBoard(kingPiece, oldPos, newPos);
                kingPiece->UpdatePosition(oldPos->first * 100, oldPos->second * 100);
                board.GetBoardMatrix()[newPos->second][newPos->first] = tempDestPiece;
                return false;
            }
            // after the check, move king back to the original place and put the tempDestPiece back
            kingPiece->UpdatePosition(oldPos->first * 100, oldPos->second * 100);
            board.UpdatePiecePositionInBoard(kingPiece, oldPos, newPos);
            board.GetBoardMatrix()[newPos->second][newPos->first] = tempDestPiece;
            return true;
        }};
        // can any pieces block the check? better if all pieces are in an array/map which we can just loop through
        // maybe keep track of who has the king in check
        // if the king is in check by two or more pieces and has no where to move, then it is checkmate
        // if the king is check by one piece, then we can figure out direction of piece relative to the king
        // for more efficient checking
        auto canPieceBlockCheck{[&](const GridPos &pos) {

        }};
        return std::any_of(possibleKingPos.begin(), possibleKingPos.end(), canKingMove);
    }
}

