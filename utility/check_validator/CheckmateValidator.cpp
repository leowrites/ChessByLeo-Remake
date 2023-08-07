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

            GridPosPtr kingPos { std::move(CalculateGridPosGivenCoord(kingPiece->GetPosition())) };
            GridPosPtr tempPos { std::make_unique<GridPos>(pos) };

            FakeMoveToNewPos(kingPos, tempPos, board);
            bool canKingMoveToGrid { true };
            if (IsKingInCheck(king->GetPieceOwner(), board))
                canKingMoveToGrid = false;
            FakeMoveFromNewPos(kingPos, tempPos, board);
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
                if (!value->GetIsAlive())
                    continue;
                std::unique_ptr<std::vector<GridPosPtr>> possiblePos { std::move(GetAllPossiblePositionsForPiece(value, board.GetBoardMatrix())) };
                if (possiblePos)
                {
                    for (auto& tempEndPos: *possiblePos)
                    {
                        GridPosPtr startPos { std::move(CalculateGridPosGivenCoord(value->GetPosition())) };
                        FakeMoveToNewPos(startPos, tempEndPos, board);
                        std::cout << board << std::endl;
                        bool isKingInCheck { IsKingInCheck(king->GetPieceOwner(), board) };
                        FakeMoveFromNewPos(startPos, tempEndPos, board);
                        if (!isKingInCheck)
                            return false;
                    }
                }
            }
        }
        std::cout << board << std::endl;
        std::cout << "Checkmate!" << std::endl;
        return true;
    }
    void CheckmateValidator::FakeMoveToNewPos(GridPosPtr& kingPos, GridPosPtr& tempPos, Board& board)
    {
        BoardMatrix& boardMatrix { board.GetBoardMatrix() };
        if (!boardMatrix[kingPos->second][kingPos->first])
            return;
        std::shared_ptr<Piece>& oldPosPiece { boardMatrix[kingPos->second][kingPos->first] };
        std::shared_ptr<Piece>& newPosPiece { boardMatrix[tempPos->second][tempPos->first] };
        oldPosPiece->UpdatePosition(tempPos->first * 100, tempPos->second * 100);
        if (newPosPiece)
            newPosPiece->UpdateIsAlive(false);
        m_movedPiece = newPosPiece;
        board.UpdatePiecePositionInBoard(oldPosPiece, tempPos, kingPos);
    };
    void CheckmateValidator::FakeMoveFromNewPos(GridPosPtr& kingPos, GridPosPtr& tempPos, Board& board)
    {
        BoardMatrix& boardMatrix { board.GetBoardMatrix() };
        std::shared_ptr<Piece>& piece { boardMatrix[tempPos->second][tempPos->first] };
        if (!piece)
            return;
        piece->UpdatePosition(kingPos->first * 100, kingPos->second * 100);
        board.UpdatePiecePositionInBoard(piece, kingPos, tempPos);
        board.GetBoardMatrix()[tempPos->second][tempPos->first] = m_movedPiece;
        if (m_movedPiece)
            m_movedPiece->UpdateIsAlive(true);
    };

    std::unique_ptr<std::vector<GridPosPtr>> CheckmateValidator::GetAllPossibleHorizontalAndVerticalPositions(const std::shared_ptr<Piece> &piece, BoardMatrix& board)
    {
        GridPosPtr currentPos { std::move(CalculateGridPosGivenCoord(piece->GetPosition())) };
        int startX { currentPos->first };
        int startY { currentPos->second };
        std::unique_ptr<std::vector<GridPosPtr>> positions { std::make_unique<std::vector<GridPosPtr>>() };
        for (int i = 1; startX + i < 8; ++i) {
            if (board[currentPos->second][startX + i] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(startX + i, currentPos->second));
            } else if (board[currentPos->second][startX + i]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(startX + i, currentPos->second));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startX - i >= 0; ++i) {
            if (board[currentPos->second][startX - i] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(startX - i, currentPos->second));
            } else if (board[currentPos->second][startX - i]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(startX - i, currentPos->second));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startY + i < 8; ++i) {
            if (board[startY + i][currentPos->first] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY + i));
            } else if (board[startY + i][currentPos->first]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY + i));
                break;
            } else {
                break;
            }
        }
        for (int i = 1; startY - i >= 0; ++i) {
            if (board[startY - i][currentPos->first] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY - i));
            } else if (board[startY - i][currentPos->first]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currentPos->first, startY - i));
                break;
            } else {
                break;
            }
        }
        return positions;
    }
    std::unique_ptr<std::vector<GridPosPtr>> CheckmateValidator::GetAllPossibleDiagonalPositions(const std::shared_ptr<Piece> &piece, BoardMatrix& board)
    {
        GridPosPtr currentPos { std::move(CalculateGridPosGivenCoord(piece->GetPosition())) };
        int startX { currentPos->first };
        int startY { currentPos->second };
        int currX;
        int currY;
        std::unique_ptr<std::vector<GridPosPtr>> positions { std::make_unique<std::vector<GridPosPtr>>() };
        // bottom right
        for (int i = 1, j = 1; startX + i < 8 && startY + i < 8; ++i, ++j) {
            currX = startX + i;
            currY = startY + j;
            if (board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // top right
        for (int i = 1, j = 1; startX + i < 8 && startY - j >= 0; ++i, ++j) {
            currX = startX + i;
            currY = startY - j;
            if (board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // top left
        for (int i = 1, j = 1; startX - i >= 0 && startY - j >= 8; ++i, ++j) {
            currX = startX - i;
            currY = startY - j;
            if (board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        // bottom left
        for (int i = 1, j = 1; startX - i >= 0 && startX + j < 8; ++i, ++j) {
            currX = startX - i ;
            currY = startY + j ;
            if (board[currY][currX] == nullptr) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
            } else if (board[currY][currX]->GetPieceOwner() != piece->GetPieceOwner()) {
                positions->push_back(std::make_unique<GridPos>(currX, currY));
                break;
            } else {
                break;
            }
        }
        return positions;
    }
    std::unique_ptr<std::vector<GridPosPtr>> CheckmateValidator::GetAllPossiblePositionsForPiece(const std::shared_ptr<Piece> &piece, BoardMatrix& board) {
        GridPosPtr gridPosPtr { std::move(CalculateGridPosGivenCoord(piece->GetPosition()))};
        switch(piece->GetPieceType())
        {
            case ChessPieceType::rook:
            {
                return GetAllPossibleHorizontalAndVerticalPositions(piece, board);
            }
            case ChessPieceType::bishop:
            {
                std::cout << "Bishop"<< std::endl;
                return GetAllPossibleDiagonalPositions(piece, board);
            }
            case ChessPieceType::queen:
            {
                std::cout << "Queen"<< std::endl;
                std::unique_ptr<std::vector<GridPosPtr>> vec1 { std::move(GetAllPossibleHorizontalAndVerticalPositions(piece, board)) };
                std::unique_ptr<std::vector<GridPosPtr>> vec2 { std::move(GetAllPossibleDiagonalPositions(piece, board)) };
                vec1->insert(vec1->end(), std::make_move_iterator(vec2->begin()), std::make_move_iterator(vec2->end()));
                return vec1;
            }
            case ChessPieceType::knight:
            {
                std::unique_ptr<std::vector<GridPosPtr>> posPtr { std::make_unique<std::vector<GridPosPtr>>() };
                std::array possiblePos {
                        GridPos {gridPosPtr->first - 1, gridPosPtr->second + 2},
                        GridPos {gridPosPtr->first + 1, gridPosPtr->second + 2},
                        GridPos {gridPosPtr->first - 1, gridPosPtr->second - 2},
                        GridPos {gridPosPtr->first + 1, gridPosPtr->second - 2},
                        GridPos {gridPosPtr->first - 2, gridPosPtr->second + 1},
                        GridPos {gridPosPtr->first + 2, gridPosPtr->second + 1},
                        GridPos {gridPosPtr->first - 2, gridPosPtr->second - 1},
                        GridPos {gridPosPtr->first + 2, gridPosPtr->second - 1}
                };
                for (auto& pos: possiblePos)
                {
                    if (0 <= pos.first and pos.first < 8 and 0<= pos.second and pos.second < 8)
                        posPtr->push_back(std::make_unique<GridPos>(pos.first, pos.second));
                }
                return posPtr;
            }
            case ChessPieceType::pawn:
            {
                GridPosPtr gridPos { std::move(CalculateGridPosGivenCoord(piece->GetPosition())) };
                return PawnMoveValidator::GetPossibleMoves(gridPos, piece->GetPieceOwner(), board);
            }
            case ChessPieceType::king:
                return nullptr;
        }
    }
}

