#include "check_validator.h"


namespace Chess {
    bool IsKingInCheckByQueen(PlayerRole playerRole, Game &game, GridPosPtr &kingPos, Board &board) {
        return false;
    }

    bool IsKingInCheckByRook(PlayerRole playerRole, Game &game, GridPosPtr &kingPos, Board &board) {
        return false;
    }

    bool IsKingInCheckByPawn(PlayerRole playerRole, Game &game, GridPosPtr &kingPos, Board &board) {
        return false;
    }

    bool IsKingInCheckByBishop(PlayerRole playerRole, Game &game, GridPosPtr &kingPos, Board &board) {
        return false;
    }

    bool IsKingInCheckByKnight(PlayerRole playerRole, Game &game, GridPosPtr &kingPos, Board& board) {
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

    bool IsKingInCheck(PlayerRole playerRole, Game &game, Board &board) {
        // Check if the king for given PlayerRole is in check
        // first find the king, this may be optimized if we track where king is on the board at all times, but for now
        // will use find_if
        std::shared_ptr<Piece>& king{ playerRole == PlayerRole::White ? board.GetWhiteKing() : board.GetBlackKing() };
        GridPosPtr kingPos{CalculateGridPosGivenCoord(king->GetPosition()->x, king->GetPosition()->y)};
        return IsKingInCheckByQueen(playerRole, game, kingPos, board) ||
               IsKingInCheckByKnight(playerRole, game, kingPos, board)
               || IsKingInCheckByBishop(playerRole, game, kingPos, board) ||
               IsKingInCheckByPawn(playerRole, game, kingPos, board)
               || IsKingInCheckByQueen(playerRole, game, kingPos, board);
    }
}