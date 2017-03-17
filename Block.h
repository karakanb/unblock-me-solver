#ifndef HW1_BLOCK_H
#define HW1_BLOCK_H

#include "globals.h"

class Block {
public:
    Block(int id, int row, int column, int length, char direction);

    Block();

    bool isHorizontal();

    void print();

    void move(int direction);

    int id;
    int row;
    int column;
    int length;
    int direction;
};


#endif //HW1_BLOCK_H
