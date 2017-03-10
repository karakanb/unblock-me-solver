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

