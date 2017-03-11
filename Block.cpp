#include "Block.h"

using namespace std;

Block::Block(int id, int row, int column, int length, char direction) : row(row), column(column), length(length),
                                                                        direction(direction) {
    this->id = id;
    this->row = row;
    this->column = column;
    this->length = length;

    if (direction == 'h') {
        this->direction = HORIZONTAL;
    } else {
        this->direction = VERTICAL;
    }
}

Block::Block() {}

void Block::print() {
    cout << "id: " << this->id << " - x: " << this->row << " - y: " << this->column << " - length: " << this->length
         << " - dir: " << this->direction << endl;
}

bool Block::isVertical() {
    return this->direction == VERTICAL;
}

bool Block::isHorizontal() {
    return this->direction == HORIZONTAL;
}

void Block::move(int direction) {
    if (this->direction == HORIZONTAL) {
        switch (direction) {
            case LEFT:
                if (this->column == 0) {
                    throw "Block cannot move to LEFT.";
                }
                this->column--;
                break;
            case RIGHT:
                if (this->column + this->length == BOARD_SIZE) {
                    throw "Block cannot move to RIGHT.";
                }
                this->column++;
                break;
            default:
                break;
        }
    } else {
        switch (direction) {
            case UP:
                if (this->row - this->length + 1 == 0) {
                    throwError("Block cannot move to up.");
                }

                this->row--;
                break;
            case DOWN:
                if (this->row == BOARD_SIZE - 1) {
                    throw "Block cannot move to RIGHT.";
                }

                this->row++;
                break;
            default:
                break;
        }
    }
}

