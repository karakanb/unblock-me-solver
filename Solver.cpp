#include "Solver.h"

Solver::Solver(const Board board) {
    this->boards.push_back(board);
}

void Solver::withDFS() {}

void Solver::withBFS() {
    Board board;
    while (!this->boards.empty()) {
        board = this->boards.front();
        this->boards.pop_front();

        if (board.isCompleted()) {
            board.print();
            this->boards.clear();
            this->constructSolutionSteps(board);
            return;
        } else {
            Board tempBoard;
            for (int i = 0; i < board.blocks.size(); ++i) {
                if (board.blocks[i].isHorizontal()) {
                    for (int j = LEFT; j <= RIGHT; ++j) {
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = board;
                            tempBoard.moveBlock(i, j);
                            this->boards.push_back(tempBoard);
                        }
                    }
                } else {
                    for (int j = UP; j <= DOWN; ++j) {
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = board;
                            tempBoard.moveBlock(i, j);
                            this->boards.push_back(tempBoard);
                        }
                    }
                }
            }
        }
        this->pastSteps.push_back(board);
    }
}

void Solver::constructSolutionSteps(Board board) {

    pp("Constructing solution steps...");
    pp2("Last ref: ", board.referencer);
    int lastReference = board.referencer;

    for (vector<Board>::iterator it = this->pastSteps.end(); it != this->pastSteps.begin(); --it) {
        //pp2("Identifier: ", it->identifier);
        if (it->identifier == lastReference) {
            pp("girdik:");
            this->steps.push_back(*it);
            lastReference = it->referencer;
        }

        //this->boards.erase(it);
    }
}

/*
void Solver::withDFS(Board board) {
    pp("a");
    if (board.isCompleted()) {
        board.print();
        throwError("Board completed successfully.");
    } else {
        int size = (int) board.blocks.size();
        for (int i = 0; i < size; ++i) {
            for (int j = LEFT; j <= DOWN; ++j) {
                if (board.canMove(board.blocks[i], j)) {
                    board.moveBlock(board.blocks[i], j);
                    this->withDFS(board);this->seenBoards.find(board) == this->seenBoards.end()
                }
            }
        }
    }
}
*/


