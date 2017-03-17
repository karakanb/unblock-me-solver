#include "Board.h"


/**
 * Copy constructor of the board object in order to not to lose identifier and referrer numbers with push-backs.
 * @param board
 * @return
 */
Board::Board(const Board &board) {

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            this->cells[i][j] = board.cells[i][j];
        }
    }
    this->identifier = board.identifier;
    this->referrer = board.referrer;
    this->blocks = board.blocks;
}

/**
 * Base constructor that sets the identifier and referrer numbers to zero.
 * @return
 */
Board::Board() {
    this->identifier = string();
    this->referrer = string();
}

/**
 * Populate the board from the file.
 * @param dataFile - File object to read data.
 */
void Board::populateBoard(std::ifstream &dataFile) {
    int row, column, length;
    int id = 1;
    char direction;
    Block tempBlock;

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
 * Pretty print the board.
 */
void Board::print(const string messageToPrint) {
    printSeperator();
    pp(messageToPrint);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << cells[i][j] << " ";
        }
        cout << endl;
    }
    printSeperator();
}

/**
 * Check if the block can move to the specified direction.
 * @param block     - Block to move.
 * @param direction - Direction to move.
 * @return          - If it can move or not.
 */
bool Board::canMove(Block block, int direction) {
    bool canMoveThere = false;
    int row = block.row;
    int column = block.column;
    int length = block.length;

    // Check the vertical and horizontal blocks separately.
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
    return canMoveThere;
}

/**
 * Move block in given index by first removing it from the board, then updating the block and re-inserting.
 * @param index
 * @param direction
 */
void Board::moveBlock(int index, int direction) {
    // Remove the block.
    this->insert(this->blocks[index], 0);

    // Move the block.
    this->blocks[index].move(direction);

    // Insert the moved block back to the board.
    this->insert(this->blocks[index]);
}

/**
 * Check if the board is completed.
 * @return
 */
bool Board::isCompleted() {
    Block blockToSave = this->getTargetBlock();
    int heroIndex = blockToSave.column + blockToSave.length;
    for (int i = heroIndex; i < BOARD_SIZE; ++i) {
        if (!this->isEmpty(blockToSave.row, i)) {
            return false;
        }
    }

    return true;
}

/**
 * Place the given variable into the board array.
 * @param block
 */
void Board::insert(Block block, int idToInsert) {

    // If the ID is not specified, use the block's id.
    if (idToInsert == -1) {
        idToInsert = block.id;
    }

    // Insert the values into the 2D board array with IDs for move checks and visualization.
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
 * Get the target block.
 * @return - target block.
 */
Block Board::getTargetBlock() {
    return this->blocks.front();
}

/**
 * Check if the cell defined with the given row and column is empty and on the board.
 * @param row
 * @param column
 * @return
 */
bool Board::isMovable(int row, int column) {
    return (this->isEmpty(row, column) && this->isOnBoard(row, column));
}

/**
 * Check if the given cell is empty or not.
 * @param row
 * @param column
 * @return
 */
bool Board::isEmpty(int row, int column) {
    return (this->cells[row][column] == 0);
}

/**
 * Check if the cell defined with the given row and column is on the board.
 * @param row
 * @param column
 * @return
 */
bool Board::isOnBoard(int row, int column) {
    return (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE);
}

/**
 * Export the board to the given file with the style of input file.
 * @param outputFile
 */
void Board::exportToFile(std::ofstream &outputFile) {
    char direction;

    // Iterate over the blocks and write to the given output file.
    for (vector<Block>::iterator it = this->blocks.begin(); it != this->blocks.end(); it++) {
        if (it->direction == HORIZONTAL) {
            direction = 'h';
        } else {
            direction = 'v';
        }

        outputFile << it->row + 1 << " " << it->column + 1 << " " << it->length << " " << direction << endl;
    }
}

/**
 * Get the hash of the board by concatenating row ids.
 * @return
 */
std::string Board::getHash() {
    string hash = string();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            hash = hash + std::to_string(this->cells[i][j]);
        }
    }

    return hash;
}