#include "CheckValidator.h"


namespace Chess {
    // TODO: bug: when we rely on getting board.GetXXX, if the piece was removed there is currently no way to tell if
    //  the piece is alive
    bool IsKingInCheckHorizontal(GridPosPtr &kingPos, GridPosPtr& otherPos, Board& board)
    {
        // 1. check if rook is on the same line
        // 2. check if there are pieces between them
        if (otherPos->first == kingPos->first)
            // same x so check y
            return !PieceInBetweenVertical(kingPos, otherPos, board);
        return false;
    }
    bool IsKingInCheckVertical(GridPosPtr &kingPos, GridPosPtr& otherPos, Board& board)
    {
        if (otherPos->second == kingPos->second)
            return !PieceInBetweenHorizontal(kingPos, otherPos, board);
        return false;
    }
    bool IsKingInCheckDiagonal(GridPosPtr &kingPos, GridPosPtr& otherPos, Board& board)
    {
        int diffX { otherPos->first - kingPos->first };
        int diffY { otherPos->second - kingPos->second};
        if (abs(diffX) != abs(diffY))
            return false;
        return !PieceInBetweenDiagonal(kingPos, otherPos, board, diffX > 0 ? 1 : -1, diffY > 0 ? 1 : -1);
    }
    bool IsKingInCheckByQueen(PlayerRole playerRole, GridPosPtr &kingPos, Board &board) {
        // note: it's possible to have more than 1 queen
        const std::unordered_set<std::shared_ptr<Piece>>& queens { playerRole == PlayerRole::White ? board.GetBlackPieces()[ChessPieceType::queen] :
                                                                   board.GetWhitePieces()[ChessPieceType::queen]};
        for (auto& queen: queens)
        {
            GridPosPtr pos { CalculateGridPosGivenCoord(queen->GetPosition()->x, queen->GetPosition()->y) };
            if (IsKingInCheckDiagonal(kingPos, pos, board) || IsKingInCheckVertical(kingPos, pos, board) ||
                    IsKingInCheckHorizontal(kingPos, pos, board))
                return true;
        }
        return false;
    }

    bool IsKingInCheckByRook(PlayerRole playerRole, GridPosPtr &kingPos, Board &board) {
        const std::unordered_set<std::shared_ptr<Piece>>& rooks {
            playerRole == PlayerRole::White ? board.GetBlackPieces()[ChessPieceType::rook] :
            board.GetWhitePieces()[ChessPieceType::rook]};
        for (const std::shared_ptr<Piece>& rook: rooks)
        {
            GridPosPtr pos { CalculateGridPosGivenCoord(rook->GetPosition()->x, rook->GetPosition()->y) };
            if (IsKingInCheckHorizontal(kingPos, pos, board) ||IsKingInCheckVertical(kingPos, pos, board))
                return true;
        }
        return false;
    }

    bool IsKingInCheckByPawn(PlayerRole playerRole, GridPosPtr &kingPos, Board &board) {
        // check top/bottom left and top right
        std::shared_ptr<Piece> targetPiece;
        int direction = (playerRole == PlayerRole::White) ? -1 : 1;
        int leftAttackCol = kingPos->first - 1;
        int rightAttackCol = kingPos->first + 1;
        if (kingPos->second + direction >= 0 && kingPos->second + direction < 8) {
            if (leftAttackCol >= 0) {
                std::shared_ptr<Piece> leftPiece = board.GetBoardMatrix()[kingPos->second + direction][leftAttackCol];
                if (leftPiece && leftPiece->GetPieceType() == ChessPieceType::pawn && leftPiece->GetPieceOwner() != playerRole)
                    return true;
            }
            if (rightAttackCol < 8) {
                std::shared_ptr<Piece> rightPiece = board.GetBoardMatrix()[kingPos->second + direction][rightAttackCol];
                if (rightPiece && rightPiece->GetPieceType() == ChessPieceType::pawn && rightPiece->GetPieceOwner() != playerRole)
                    return true;
            }
        }
        return false;
    }

    bool IsKingInCheckByBishop(PlayerRole playerRole, GridPosPtr &kingPos, Board &board) {
        const std::unordered_set<std::shared_ptr<Piece>>& bishops {
                playerRole == PlayerRole::White ? board.GetBlackPieces()[ChessPieceType::bishop] :
                board.GetWhitePieces()[ChessPieceType::bishop]};
        for (auto& bishop: bishops)
        {
            GridPosPtr pos { CalculateGridPosGivenCoord(bishop->GetPosition()->x, bishop->GetPosition()->y) };
            if (IsKingInCheckDiagonal(kingPos, pos, board))
                return true;
        }
        return false;
    }

    bool IsKingInCheckByKnight(PlayerRole playerRole, GridPosPtr &kingPos, Board& board) {
        std::array possiblePos{
                GridPos{kingPos->first - 1, kingPos->second + 2},
                GridPos{kingPos->first + 1, kingPos->second + 2},
                GridPos{kingPos->first - 1, kingPos->second - 2},
                GridPos{kingPos->first + 1, kingPos->second - 2},
                GridPos{kingPos->first - 2, kingPos->second + 1},
                GridPos{kingPos->first + 2, kingPos->second + 1},
                GridPos{kingPos->first - 2, kingPos->second - 1},
                GridPos{kingPos->first + 2, kingPos->second - 1}
        };
        auto isEnemyKnight = [&playerRole, &board](GridPos& pos)
        {
            if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7)
                return false;
            if (!board.GetBoardMatrix()[pos.second][pos.first])
                return false;
            return board.GetBoardMatrix()[pos.second][pos.first]->GetPieceOwner() != playerRole
            && board.GetBoardMatrix()[pos.second][pos.first]->GetPieceType() == ChessPieceType::knight;
        };
        GridPos* gridPos = std::find_if(possiblePos.begin(), possiblePos.end(), isEnemyKnight);
        if (gridPos != possiblePos.end())
            return true;
        return false;
    }

    bool IsKingInCheck(PlayerRole playerRole, Board &board) {
        // Check if the king for given PlayerRole is in check
        // first find the king, this may be optimized if we track where king is on the board at all times, but for now
        // will use find_if
        const std::shared_ptr<Piece>& king{ playerRole == PlayerRole::White ? board.GetWhiteKing() : board.GetBlackKing() };
        GridPosPtr kingPos{CalculateGridPosGivenCoord(king->GetPosition()->x, king->GetPosition()->y)};
        return IsKingInCheckByQueen(playerRole, kingPos, board) ||
               IsKingInCheckByKnight(playerRole, kingPos, board) ||
               IsKingInCheckByBishop(playerRole, kingPos, board) ||
               IsKingInCheckByPawn(playerRole, kingPos, board) ||
                IsKingInCheckByRook(playerRole, kingPos, board);
    }
}