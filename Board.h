//
// Created by burak on 10.03.2017.
//

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

    void printBoard();

    bool isEmpty(int row, int column);


    inline int &operator()(int x, int y) {
        return board[x][y];
    }

private:
    void fillTheBoard(Block block);
};


#endif //HW1_BOARD_H
