//
// Created by taotianyi on 11/17/17.
//

#include <iostream>
#include "Move.h"

Move::Move() = default;

Move::Move(int rowIndex, int columnIndex, int moveType) {
    if(rowIndex != 1 && rowIndex != 2 && rowIndex != 3){
        std::cout << "Invalid argument rowIndex: expected 1 or 2 or 3, give " << rowIndex << std::endl;
        return;
    }
    if(columnIndex != 1 && columnIndex != 2 && columnIndex != 3){
        std::cout << "Invalid argument columnIndex: expected 1 or 2 or 3, give " << columnIndex << std::endl;
        return;
    }
    if(moveType != 1 && moveType != -1){
        std::cout << "Invalid argument moveType: expected 1 or -1, give " << moveType << std::endl;
        return;
    }
    x = rowIndex;
    y = columnIndex;
    type = moveType;
}

int Move::getRowIndex() {
    return x;
}

int Move::getColumnIndex() {
    return y;
}

int Move::getType() {
    return type;
}

