//
// Created by burak on 10.03.2017.
//

#ifndef HW1_BLOCK_H
#define HW1_BLOCK_H

#include <iostream>
#include "globals.h"
class Block {
public:
    Block(int id, int row, int column, int length, char direction);

    Block();
    bool isHorizontal();
    bool isVertical();

    void print();
    int id;
    int row;
    int column;
    int length;
    int direction;
};


#endif //HW1_BLOCK_H
