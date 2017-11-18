//
// Created by taotianyi on 11/17/17.
//

#ifndef TIC_TAC_TOE_MOVE_H
#define TIC_TAC_TOE_MOVE_H


class Move {
protected:
    //x can be 1, 2, 3
    int x;
    //y can be 1, 2, 3
    int y;
    //type can be 1, -1
    //1 for circle, -1 for cross
    int type;

    //(x, y) in every position
    // ╔═══════╦═══════╦═══════╗
    // ║ (1,1) ║ (1,2) ║ (1,3) ║
    // ╠═══════╬═══════╬═══════╣
    // ║ (3,1) ║ (2,2) ║ (2,3) ║
    // ╠═══════╬═══════╬═══════╣
    // ║ (3,1) ║ (3,2) ║ (3,3) ║
    // ╚═══════╩═══════╩═══════╝
public:
    Move();

    Move(int x, int y, int type);

    int getRowIndex();

    int getColumnIndex();

    int getType();

};


#endif //TIC_TAC_TOE_MOVE_H
