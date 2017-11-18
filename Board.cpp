//
// Created by taotianyi on 11/17/17.
//

#include <iostream>
#include "Board.h"

Board::Board() {
    boardRepresentation = std::vector<std::vector<int>>(3);
    for(int i = 0; i < 3; i++){
        boardRepresentation[i] = std::vector<int>(3);
        boardRepresentation[i][0] = 0;
        boardRepresentation[i][1] = 0;
        boardRepresentation[i][2] = 0;
    }
    firstType = -1;
    over = false;
    canPlay = true;
    expectedType = -1;
}

Board::Board(const Board & board) {
    boardRepresentation = std::vector<std::vector<int>>(3);
    for(int i = 0; i < 3; i++){
        boardRepresentation[i] = std::vector<int>(3);
        boardRepresentation[i][0] = board.boardRepresentation[i][0];
        boardRepresentation[i][1] = board.boardRepresentation[i][1];
        boardRepresentation[i][2] = board.boardRepresentation[i][2];
    }
    firstType = board.firstType;
    over = board.over;
    canPlay = board.canPlay;
    expectedType = board.expectedType;
    optimalMoves = std::vector<Move>(board.optimalMoves.size());
    for(int i = 0; i < board.optimalMoves.size(); i++){
        Move move = board.optimalMoves[i];
        optimalMoves[i] = Move(move.getRowIndex(), move.getColumnIndex(), move.getType());
    }
    winnerAfterOptimalMove = board.winnerAfterOptimalMove;
}

Board::Board(int firstType) {
    if (firstType != 1 && firstType != -1) {
        std::cout << "Invalid argument firstType: expected 1 or -1, give " << firstType << std::endl;
        return;
    }
    boardRepresentation = std::vector<std::vector<int>>(3);
    for(int i = 0; i < 3; i++){
        boardRepresentation[i] = std::vector<int>(3);
        boardRepresentation[i][0] = 0;
        boardRepresentation[i][1] = 0;
        boardRepresentation[i][2] = 0;
    }
    this->firstType = firstType;
    over = false;
    canPlay = true;
    expectedType = firstType;
}

Board::Board(const std::vector<std::vector<int>> &representation, int firstType) {
    if (firstType != 1 && firstType != -1) {
        std::cout << "Invalid argument firstType: expected 1 or -1, give " << firstType << std::endl;
        return;
    }
    if (representation.size() < 3) {
        std::cout << "Invalid argument representation: expected 3 * 3 two-dim array" << std::endl;
        return;
    }
    int firstPlayerCount = 0;
    int secondPlayerCount = 0;
    std::vector<std::vector<int>> tempRepresentation(3);
    for (int i = 0; i < 3; i += 1) {
        tempRepresentation[i] = std::vector<int>(3);
        if (representation[i].size() < 3) {
            std::cout << "Invalid argument representation: expected 3 * 3 two-dim array" << std::endl;
            return;
        }
        for (int j = 0; j < 3; j += 1) {
            if (representation[i][j] != 1 && representation[i][j] != -1 && representation[i][j] != 0) {
                std::cout << "Invalid argument representation: expected -1,0,1 in any position, give "
                          << representation[i][j] << std::endl;
                return;
            } else {
                tempRepresentation[i][j] = representation[i][j];
                if (representation[i][j] == firstType) {
                    firstPlayerCount++;
                } else if (representation[i][j] == -firstType) {
                    secondPlayerCount++;
                }
            }
        }
    }
    if (firstPlayerCount == secondPlayerCount || firstPlayerCount == (secondPlayerCount + 1)) {
        this->boardRepresentation = tempRepresentation;
        this->firstType = firstType;
        over = this->isOver();
        canPlay = !(this->isFull());
        expectedType = this->getExpectedType();
    } else {
        std::cout << "Invalid board: first player plays for " << firstPlayerCount
                  << " times while second player plays for " << secondPlayerCount << " times, which is impossible"
                  << std::endl;
        return;
    }
}

Board Board::nextBoard(Move move) {
    Board toReturn = Board(*this);
    //check expected type
    if (move.getType() != expectedType) {
        std::cout << "Invalid argument move: expected mark type is " << expectedType << ", give" << move.getType()
                  << std::endl;
        return *this;
    }
    //check place occupied
    if (boardRepresentation[move.getRowIndex() - 1][move.getColumnIndex() - 1] != 0) {
        std::cout << "Invalid argument move: (" << move.getRowIndex() - 1 << ", " << move.getColumnIndex() - 1
                  << ") already occupied" << std::endl;
        return *this;
    }
    toReturn.boardRepresentation[move.getRowIndex() - 1][move.getColumnIndex() - 1] = move.getType();
    toReturn.over = toReturn.isOver();
    toReturn.canPlay = !(toReturn.isFull());
    toReturn.expectedType = toReturn.getExpectedType();
    return toReturn;
}

int Board::getExpectedType() {
    if (!canPlay) {
        return 0;
    }
    int firstPlayerCount = 0;
    int secondPlayerCount = 0;
    for (int i = 0; i < 3; i += 1) {
        for (int j = 0; j < 3; j += 1) {
            if (boardRepresentation[i][j] == firstType) {
                firstPlayerCount++;
            } else if (boardRepresentation[i][j] == -firstType) {
                secondPlayerCount++;
            }
        }
    }
    if (firstPlayerCount == secondPlayerCount) {
        return firstType;
    } else if (firstPlayerCount == (secondPlayerCount + 1)) {
        return -firstType;
    } else {
        std::cout << "this is an invalid board, first player plays for " << firstPlayerCount
                  << " times while second player plays for " << secondPlayerCount << " times, which is impossible"
                  << std::endl;
        return 0;
    }
}

bool Board::isFull() {
    for (int i = 0; i < 3; i += 1) {
        for (int j = 0; j < 3; j += 1) {
            if (boardRepresentation[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Board::isOver() {
    if (!canPlay) {
        return true;
    }
    for (int i = 0; i < 3; i++) {
        //check rows
        int sum = boardRepresentation[i][0] + boardRepresentation[i][1] + boardRepresentation[i][2];
        if (sum == 3 || sum == -3) {
            return true;
        }
        //check cols
        sum = boardRepresentation[0][i] + boardRepresentation[1][i] + boardRepresentation[2][i];
        if (sum == 3 || sum == -3) {
            return true;
        }
    }
    //check diagonal
    int sum = boardRepresentation[0][0] + boardRepresentation[1][1] + boardRepresentation[2][2];
    if (sum == 3 || sum == -3) {
        return true;
    }
    sum = boardRepresentation[0][2] + boardRepresentation[1][1] + boardRepresentation[2][0];
    if (sum == 3 || sum == -3) {
        return true;
    }
    return false;
}

int Board::getWinnerMarkType() {
    for (int i = 0; i < 3; i++) {
        //check rows
        int sum = boardRepresentation[i][0] + boardRepresentation[i][1] + boardRepresentation[i][2];
        if (sum == 3) {
            return 1;
        }
        if (sum == -3) {
            return -1;
        }
        //check cols
        sum = boardRepresentation[0][i] + boardRepresentation[1][i] + boardRepresentation[2][i];
        if (sum == 3) {
            return 1;
        }
        if (sum == -3) {
            return -1;
        }
    }
    //check diagonal
    int sum = boardRepresentation[0][0] + boardRepresentation[1][1] + boardRepresentation[2][2];
    if (sum == 3) {
        return 1;
    }
    if (sum == -3) {
        return -1;
    }
    sum = boardRepresentation[0][2] + boardRepresentation[1][1] + boardRepresentation[2][0];
    if (sum == 3) {
        return 1;
    }
    if (sum == -3) {
        return -1;
    }
    return 0;
}

std::vector<Move> Board::getAvailableMoves(){
    if(!canPlay){
        return std::vector<Move>(0);
    }
    std::vector<Move> moves(0);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(boardRepresentation[i][j] == 0){
                moves.emplace_back(Move(i + 1, j+1, expectedType));
            }
        }
    }
    return moves;
}

std::vector<Move> Board::getOptimalMoves() {
    return optimalMoves;
}

int Board::getWinnerTypeAfterOptimalMove(){
    return winnerAfterOptimalMove;
}

void Board::printBoard() {
    //    ╔═══╦═══╦═══╗
    //    ║ O ║ X ║ X ║
    //    ╠═══╬═══╬═══╣
    //    ║ X ║ O ║ X ║
    //    ╠═══╬═══╬═══╣
    //    ║ O ║ O ║   ║
    //    ╚═══╩═══╩═══╝
    std::vector<std::vector<char>> marks(3);
    for (int i = 0; i < 3; i++) {
        marks[i] = std::vector<char>(3);
        for (int j = 0; j < 3; j++) {
            if (boardRepresentation[i][j] == -1) {
                marks[i][j] = 'X';
            } else if (boardRepresentation[i][j] == 1) {
                marks[i][j] = 'O';
            } else {
                marks[i][j] = ' ';
            }
        }
    }
    std::cout << "\t╔═══╦═══╦═══╗\n";
    std::cout << "\t║ " << marks[0][0] << " ║ " << marks[0][1] << " ║ " << marks[0][2] << " ║\n";
    std::cout << "\t╠═══╬═══╬═══╣\n";
    std::cout << "\t║ " << marks[1][0] << " ║ " << marks[1][1] << " ║ " << marks[1][2] << " ║\n";
    std::cout << "\t╠═══╬═══╬═══╣\n";
    std::cout << "\t║ " << marks[2][0] << " ║ " << marks[2][1] << " ║ " << marks[2][2] << " ║\n";
    std::cout << "\t╚═══╩═══╩═══╝" << std::endl;
}

void Board::calculateOptimal() {
    if(over){
        optimalMoves = std::vector<Move>(0);
        winnerAfterOptimalMove = getWinnerMarkType();
        return;
    }
    std::vector<Move> candidateMoves = getAvailableMoves();
    bool canWin = false;
    bool canDraw = false;
    std::vector<Move> winMoves(0);
    std::vector<Move> drawMoves(0);
    std::vector<Move> loseMoves(0);
    for(Move move: candidateMoves){
        Board newBoard = nextBoard(move);
        newBoard.calculateOptimal();
        int newBoardWinnerType = newBoard.winnerAfterOptimalMove;
        if(newBoardWinnerType == expectedType){
            canWin = true;
            winMoves.push_back(move);
        } else if(newBoardWinnerType == -expectedType) {
            loseMoves.push_back(move);
        } else{
            canDraw = true;
            drawMoves.push_back(move);
        }
    }
    if(canWin){
        optimalMoves = winMoves;
        winnerAfterOptimalMove = expectedType;
    } else if(canDraw){
        optimalMoves = drawMoves;
        winnerAfterOptimalMove = 0;
    } else{
        optimalMoves = loseMoves;
        winnerAfterOptimalMove = -expectedType;
    }
}
