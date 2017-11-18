//
// Created by taotianyi on 11/17/17.
//

#ifndef TIC_TAC_TOE_BOARD_H
#define TIC_TAC_TOE_BOARD_H


#include <vector>
#include "Move.h"

class Board {
protected:
    //use a two-dim int array to represent the tic-tac-toe board, 1 for circle, -1 for cross, 0 for nothing
    std::vector<std::vector<int>> boardRepresentation;
    //For example, let O represent player1-circle and X represent player2-cross and let blank space present nothing,
    //Then
    //[
    //  [1  , -1, -1],
    //  [-1 , 1 , -1],
    //  [1  , 1 , 0 ]
    //]
    //   can represent following board:
    //    ╔═══╦═══╦═══╗
    //    ║ O ║ X ║ X ║
    //    ╠═══╬═══╬═══╣
    //    ║ X ║ O ║ X ║
    //    ╠═══╬═══╬═══╣
    //    ║ O ║ O ║   ║
    //    ╚═══╩═══╩═══╝
    //`firstType` indicates which mark is placed first. 1 for circle, -1 for cross
    int firstType;
    //`over` indicates if current board shows a winner or all 9 positions are occupied.
    //true for either condition is true, false for neither condition is true
    bool over;
    //`canPlay` indicates if all 9 positions are occupied
    //true for condition is true, false for condition is false
    //note: if canPlay is false, then over is true
    bool canPlay;
    //`expectedType` indicates which mark should play the next move
    int expectedType;

    std::vector<Move> optimalMoves;

    int winnerAfterOptimalMove;

public:
    Board();

    Board(const Board &);

    Board(int firstType);

    Board(const std::vector<std::vector<int>> &representation, int firstType);

    Board nextBoard(Move move);

    int getExpectedType();

    bool isFull();

    bool isOver();

    int getWinnerMarkType();

    std::vector<Move> getAvailableMoves();

    void calculateOptimal();

    std::vector<Move> getOptimalMoves();

    int getWinnerTypeAfterOptimalMove();


    void printBoard();
};


#endif //TIC_TAC_TOE_BOARD_H
