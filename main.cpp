#include <iostream>
#include "Board.h"

void startGame();

int main() {
    srand((unsigned) time(NULL));
    std::cout << "Welcome to play tic-tac-toe!" << std::endl;
    std::string cmd;
    while (true) {
        std::cout << "Input start to start or quit to quit." << std::endl;
        std::cin >> cmd;
        if (cmd == "start") {
            startGame();
        } else if (cmd == "quit") {
            exit(0);
        } else {
            std::cout << "Unknown action: " << cmd << std::endl;
        }
    }
    Board b;
    b = b.nextBoard(Move(1, 1, -1));
    b = b.nextBoard(Move(1, 2, 1));
    while (true) {
        b.printBoard();
        if (b.isOver()) {
            std::cout << b.getWinnerMarkType() << " wins" << std::endl;
            break;
        }
        b.calculateOptimal();
        std::vector<Move> bestNextMoves = b.getOptimalMoves();
        Move move = bestNextMoves[bestNextMoves.size() / 2];
        b = b.nextBoard(move);
    }
    return 0;
}

void startGame() {
    std::string cmd;
    std::cout << "Note:" << std::endl;
    std::cout << "Input (x,y) as your next move. x indicates the row while y indicates the column." << std::endl;
    std::cout << "╔═══════╦═══════╦═══════╗\n"
            "║ (1,1) ║ (1,2) ║ (1,3) ║\n"
            "╠═══════╬═══════╬═══════╣\n"
            "║ (3,1) ║ (2,2) ║ (2,3) ║\n"
            "╠═══════╬═══════╬═══════╣\n"
            "║ (3,1) ║ (3,2) ║ (3,3) ║\n"
            "╚═══════╩═══════╩═══════╝" << std::endl;
    std::cout << "Will you play first? Input yes then you will play first, input no then you will play after, input any"
            " other instructions will lead to first player being randomly decided" << std::endl;

    std::cin >> cmd;
    bool humanFirst;
    if (cmd == "yes") {
        humanFirst = true;
    } else if (cmd == "no") {
        humanFirst = false;
    } else {
        humanFirst = (random() % 2 == 0);
    }

    std::cout << "Will you play as circle or cross? Input O(Alphabet O not zero) for circle, X for cross. Input any"
            " other instructions will lead to your mark being randomly decided" << std::endl;

    int humanMark;
    std::cin >> cmd;
    if (cmd == "O") {
        humanMark = 1;
    } else if (cmd == "X") {
        humanMark = -1;
    } else {
        humanMark = (random() % 2 == 0) ? 1 : -1;
    }

    Board board(humanFirst ? humanMark : -humanMark);

    while (true) {
        board.printBoard();
        if (board.isOver()) {
            if (board.getWinnerMarkType() == 0) {
                std::cout << "Draw!" << std::endl;
            } else if (board.getWinnerMarkType() == humanMark) {
                std::cout << "You win!" << std::endl;
            } else {
                std::cout << "Computer win!" << std::endl;
            }
            break;
        }
        Move move;
        if (board.getExpectedType() == humanMark) {
            std::cout << "Your move:" << std::endl;
            while (true) {
                std::cin >> cmd;
                int row = -1;
                int col = -1;
                bool tokenLegal = true;
                bool tokenValid = false;
                unsigned long leftParenthesisPosition = cmd.find_first_of('(');
                unsigned long commaPosition = cmd.find_first_of(',');
                unsigned long rightParenthesisPosition = cmd.find_first_of(')');
                if (leftParenthesisPosition == std::string::npos || commaPosition == std::string::npos ||
                    rightParenthesisPosition == std::string::npos) {
                    tokenLegal = false;
                } else {
                    std::string numStr1 = cmd.substr(leftParenthesisPosition + 1,
                                                     commaPosition - leftParenthesisPosition - 1);
                    std::string numStr2 = cmd.substr(commaPosition + 1, rightParenthesisPosition - commaPosition - 1);
//                    std::cout << numStr1 << "\t" << numStr2 << std::endl;
                    if (numStr1 == "1") {
                        row = 1;
                    } else if (numStr1 == "2") {
                        row = 2;
                    } else if (numStr1 == "3") {
                        row = 3;
                    } else {
                        tokenLegal = false;
                    }
                    if (numStr2 == "1") {
                        col = 1;
                    } else if (numStr2 == "2") {
                        col = 2;
                    } else if (numStr2 == "3") {
                        col = 3;
                    } else {
                        tokenLegal = false;
                    }
                }
                if (!tokenLegal) {
                    std::cout << "Input not legal, please input something like (1,2)." << std::endl;
                    continue;
                }

                std::vector<Move> validMoves = board.getAvailableMoves();
                for (Move validMove : validMoves) {
                    if (validMove.getRowIndex() == row && validMove.getColumnIndex() == col) {
                        move = validMove;
                        tokenValid = true;
                        break;
                    }
                }
                if (!tokenValid) {
                    std::cout << "Input not valid, position already occupied. Please input again." << std::endl;
                    continue;
                }
                break;
            }
        }else{
            std::cout << "Computer's move:" << std::endl;
            board.calculateOptimal();
            std::vector<Move> validMoves = board.getOptimalMoves();
            move = validMoves[rand() % validMoves.size()];
            std::cout << "(" << move.getRowIndex() << "," << move.getColumnIndex() << ")" << std::endl;
        }
        board = board.nextBoard(move);
    }
}