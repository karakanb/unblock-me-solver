#ifndef UNBLOCK_ME_SOLVER_BOARD_H
#define UNBLOCK_ME_SOLVER_BOARD_H

#include <fstream>
#include <vector>
#include "Block.h"
#include "globals.h"

using namespace std;


class Board {
public:
    int cells[BOARD_SIZE][BOARD_SIZE] = {{0}};
    string identifier;
    string referrer;
    vector<Block> blocks;

    Board();

    Board(const Board &obj);

    void populateBoard(std::ifstream &dataFile);

    void exportToFile(std::ofstream &outputFile);

    string getHash();

    void print(const string messageToPrint = "");

    bool canMove(Block block, int direction);

    void moveBlock(int index, int direction);

    bool isCompleted();

    bool operator<(const Board &board) const {
        return (bool) (identifier.compare(board.identifier));
    }

private:

    void insert(Block block, int idToInsert = -1);

    Block getTargetBlock();

    bool isMovable(int row, int column);

    bool isOnBoard(int row, int column);

    bool isEmpty(int row, int column);
};


#endif //UNBLOCK_ME_SOLVER_BOARD_H
