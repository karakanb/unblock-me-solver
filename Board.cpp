#include "Board.h"

void Board::populateBoard(std::ifstream &dataFile) {
    int row, column, length;
    int id = 1;
    char direction;
    Block tempBlock;

    // Get the target block.
    dataFile >> row >> column >> length >> direction;
    this->targetBlock = Block(id++, row - 1, column - 1, length, direction);
    this->insert(this->targetBlock);

    // Collect the other blocks.
    while (dataFile >> row >> column >> length >> direction) {
        // Construct a temporary block.
        tempBlock = Block(id++, row - 1, column - 1, length, direction);

        // Fill the board storage variables.
        this->blocks.push_back(tempBlock);
        this->insert(tempBlock);
    }
}

Board::Board() {}

/**
 * Place the given variable into the board array.
 * @param block
 */
void Board::insert(Block block, int idToInsert) {
    if (idToInsert == -1) {
        idToInsert = block.id;
    }

    if (block.direction == HORIZONTAL) {
        for (int i = block.column; i < block.column + block.length; ++i) {
            this->board[block.row][i] = idToInsert;
        }
    } else {
        for (int i = block.row; i > block.row - block.length; --i) {
            this->board[i][block.column] = idToInsert;
        }
    }
}

/**
 * Pretty print the board.
 */
void Board::print() {
    cout << endl << "===========================" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool Board::canMove(int row, int column) {
    return (row < 6 && column > 6 && this->board[row][column] == 0);
}

void Board::moveBlock(Block block, int direction) {
    this->insert(block, 0);
    block.move(direction);
    this->insert(block);
}
