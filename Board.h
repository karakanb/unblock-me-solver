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

    Board(const Board &obj);

    int cells[BOARD_SIZE][BOARD_SIZE] = {{0}};
    long identifier;
    long referencer;
    Block targetBlock;
    vector<Block> blocks;

    long getHash() const;

    void populateBoard(std::ifstream &dataFile);

    void print();

    bool canMove(Block block, int direction);

    bool isEmpty(int row, int column);

    bool isCompleted();

    Block getPrisoner();

    void moveBlock(int index, int direction);

    void insert(Block block, int idToInsert = -1);

    inline int &operator()(int x, int y) {
        return cells[x][y];
    }

    bool operator<(const Board &board) const {
        return identifier < board.identifier;
    }

private:
    bool isOnBoard(int row, int column);

    bool isMovable(int row, int column);
};


#endif //HW1_BOARD_H
