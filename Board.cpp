#include <assert.h>
#include "Board.h"

void Board::populateBoard(std::ifstream &dataFile) {
    int row, column, length;
    int id = 1;
    char direction;
    Block tempBlock;

    // Get the target block.
    dataFile >> row >> column >> length >> direction;
    this->targetBlock = Block(id++, row - 1, column - 1, length, direction);
    this->blocks.push_back(this->targetBlock);
    this->insert(this->targetBlock);

    // Collect the other blocks.
    while (dataFile >> row >> column >> length >> direction) {
        // Construct a temporary block.
        tempBlock = Block(id++, row - 1, column - 1, length, direction);

        // Fill the cells storage variables.
        this->blocks.push_back(tempBlock);
        this->insert(tempBlock);
    }
}


/**
 * Place the given variable into the board array.
 * @param block
 */
void Board::insert(Block block, int idToInsert) {
    if (idToInsert == -1) {
        idToInsert = block.id;
    }

    if (block.isHorizontal()) {
        for (int i = block.column; i < block.column + block.length; ++i) {
            this->cells[block.row][i] = idToInsert;
        }
    } else {
        for (int i = block.row; i > block.row - block.length; --i) {
            this->cells[i][block.column] = idToInsert;
        }
    }
}

/**
 * Pretty print the board.
 */
void Board::print() {
    cout << endl << "===========================" << endl << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << cells[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "===========================" << endl;
}

bool Board::canMove(Block block, int direction) {
    bool canMoveThere = false;
    int row = block.row;
    int column = block.column;
    int length = block.length;

    if (block.isHorizontal()) {
        switch (direction) {
            case LEFT:
                if (isMovable(row, column - 1)) {
                    canMoveThere = true;
                }
                break;
            case RIGHT:
                if (isMovable(row, column + length)) {
                    canMoveThere = true;
                }
                break;
            default:
                break;
        }
    } else {
        switch (direction) {
            case UP:
                if (isMovable(row - length, column)) {
                    canMoveThere = true;
                }
                break;
            case DOWN:
                if (isMovable(row + 1, column)) {
                    canMoveThere = true;
                }
                break;
            default:
                break;
        }
    }
    /*
    pp("--");
    pp2("BlockId: ", block.id);
    pp2("direction: ", direction);
    pp2("can it move: ", canMoveThere);
    pp("--");
     */
    return canMoveThere;
}

void Board::moveBlock(int index, int direction) {
    this->insert(this->blocks[index], 0);
    this->blocks[index].move(direction);
    this->insert(this->blocks[index]);
}

Block Board::getPrisoner() {
    return this->blocks.front();
}

bool Board::isEmpty(int row, int column) {
    return (this->cells[row][column] == 0);
}

bool Board::isCompleted() {
    Block blockToSave = this->getPrisoner();
    int heroIndex = blockToSave.column + blockToSave.length;
    for (int i = heroIndex; i < BOARD_SIZE; ++i) {
        if (!this->isEmpty(blockToSave.row, i)) {
            return false;
        }
    }

    return true;
}

bool Board::isOnBoard(int row, int column) {
    return (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE);
}

bool Board::isMovable(int row, int column) {
    return (this->isEmpty(row, column) && this->isOnBoard(row, column));
}

Board::Board(const Board& board) {

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            this->cells[i][j] = board.cells[i][j];
        }
    }
    this->identifier = rand();
    this->referencer = board.identifier;

    this->targetBlock = board.targetBlock;
    this->blocks = board.blocks;
}

Board::Board() {
    this->identifier = 0;
}
