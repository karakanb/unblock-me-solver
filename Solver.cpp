#include "Solver.h"

Solver::Solver(Board board) {
    this->boards.push_back(board);
}

void Solver::withDFS() {}

void Solver::withBFS() {
    Board board;
    this->boards.front().identifier = 0;
    this->pastSteps[this->boards.front().getHash()] = this->boards.front();

    while (!this->boards.empty()) {

        // Get the next board and remove it from the list.
        board = this->boards.front();

        // Move the board to the past steps.
        this->pastSteps[board.getHash()] = board;
        this->boards.pop_front();

        if (board.isCompleted()) {
            board.print();
            this->boards.clear();
            this->constructSolutionSteps(board);
            return;
        } else {
            Board tempBoard;

            // Construct the possible movement boards and push to the queue.
            for (int i = 0; i < board.blocks.size(); ++i) {
                if (board.blocks[i].isHorizontal()) {
                    for (int j = LEFT; j <= RIGHT; ++j) {
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = board;
                            tempBoard.moveBlock(i, j);
                            this->boards.push_back(move(tempBoard));
                        }
                    }
                } else {
                    for (int j = UP; j <= DOWN; ++j) {
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = board;
                            tempBoard.moveBlock(i, j);
                            this->boards.push_back(move(tempBoard));
                        }
                    }
                }
            }
        }
    }
}

void Solver::constructSolutionSteps(Board board) {

    pp("Constructing solution steps...");
    pp2("Last ref: ", board.getHash());
    long lastReference = board.referencer;

    pp2("past-step size: ", this->pastSteps.size());
}
