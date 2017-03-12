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
    cout << "id: " << this->id << " - row: " << this->row << " - col: " << this->column << " - length: " << this->length
         << " - dir: " << this->direction << endl;
}

bool Block::isVertical() {
    return this->direction == VERTICAL;
}

bool Block::isHorizontal() {
    return this->direction == HORIZONTAL;
}

void Block::move(int direction) {
    if (this->isHorizontal()) {
        switch (direction) {
            case LEFT:
                if (this->column == 0) {
                    throwError("Block cannot move LEFT.", this->id);
                }
                this->column--;
                break;
            case RIGHT:
                if (this->column + this->length == BOARD_SIZE) {
                    throwError("Block cannot move RIGHT.", this->id);
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
                    throwError("Block cannot move up.", this->id);
                }

                this->row--;
                break;
            case DOWN:
                if (this->row == BOARD_SIZE - 1) {
                    throwError("Block cannot move down.", this->id);
                }

                this->row++;
                break;
            default:
                break;
        }
    }
}

long Block::hash() const {
    return this->id | this->row << 8 | this->column << 16;
}

