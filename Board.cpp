#include "Board.h"

void Board::populateBoard(std::ifstream &dataFile) {
    int row, column, length;
    int id = 1;
    char direction;
    Block tempBlock;

    // Get the target block.
    dataFile >> row >> column >> length >> direction;
    this->targetBlock = Block(id++, row, column, length, direction);
    this->fillTheBoard(this->targetBlock);

    // Collect the other blocks.
    while (dataFile >> row >> column >> length >> direction) {
        // Construct a temporary block.
        tempBlock = Block(id++, row, column, length, direction);

        // Fill the board storage variables.
        this->blocks.push_back(tempBlock);
        this->fillTheBoard(tempBlock);
    }
}

Board::Board() {}

/**
 * Place the given variable into the board array.
 * @param block
 */
void Board::fillTheBoard(Block block) {
    if (block.direction == HORIZONTAL) {
        for (int i = block.column - 1; i < block.column + block.length - 1; ++i) {
            this->board[block.row - 1][i] = block.id;
        }
    } else {
        for (int i = block.row - 1; i >= block.row - block.length; --i) {
            this->board[i][block.column - 1] = block.id;
        }
    }
}

/**
 * Pretty print the board.
 */
void Board::printBoard() {
    cout << endl << "===========================" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool Board::isEmpty(int  row, int column) {
    return this->board[row][column] == 0;
}

