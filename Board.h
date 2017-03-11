#ifndef HW1_BOARD_H
#define HW1_BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Block.h"
#include "globals.h"

using namespace std;


class Board {
public:
    Board();

    int board[BOARD_SIZE][BOARD_SIZE] = {{0}};
    Block targetBlock;
    vector<Block> blocks;

    void populateBoard(std::ifstream &dataFile);

    void print();

    bool canMove(int row, int column);

    void moveBlock(Block block, int direction);

    inline int &operator()(int x, int y) {
        return board[x][y];
    }

private:
    void insert(Block block, int idToInsert = -1);
};


#endif //HW1_BOARD_H
