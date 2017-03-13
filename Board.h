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
    int cells[BOARD_SIZE][BOARD_SIZE] = {{0}};
    long identifier;
    long referrer;
    vector<Block> blocks;

    Board();

    Board(const Board &obj);

    void populateBoard(std::ifstream &dataFile);
    void exportToFile(std::ofstream &outputFile);

    void print(const string messageToPrint = "");

    bool canMove(Block block, int direction);

    void moveBlock(int index, int direction);

    bool isCompleted();

    bool operator<(const Board &board) const {
        return identifier < board.identifier;
    }

private:

    void insert(Block block, int idToInsert = -1);

    Block getTargetBlock();

    bool isMovable(int row, int column);

    bool isOnBoard(int row, int column);

    bool isEmpty(int row, int column);
};


#endif //HW1_BOARD_H