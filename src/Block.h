#ifndef UNBLOCK_ME_SOLVER_BLOCK_H
#define UNBLOCK_ME_SOLVER_BLOCK_H

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


#endif //UNBLOCK_ME_SOLVER_BLOCK_H
