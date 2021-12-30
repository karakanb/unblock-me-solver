#include "Solver.h"

/**
 * Base constructor that pushes the root node to the double-ended queue.
 * @param board
 * @return
 */
Solver::Solver(Board board) {
    this->boards.push_back(board);
}

/**
 * Construct the solution steps from the pastSteps vector by using the reference chain.
 * @param board
 */
void Solver::constructSolutionSteps(Board board) {

    // Remove the possible boards.
    this->boards.clear();

    // Process the solution board first.
    string lastReference = board.referrer;
    this->steps.push_back(board);

    // Construct the solution steps from the reference chain.
    while (lastReference != "") {
        this->steps.push_back(this->pastSteps[lastReference]);
        lastReference = this->pastSteps[lastReference].referrer;
    }

    // Get the number of steps taken to find the solution.
    this->numberOfNodes = this->pastSteps.size();

    // Push the initial state of the board to the vector.
    this->steps.push_back((this->pastSteps.begin())->second);

    // Remove the useless past steps.
    this->pastSteps.clear();

    return;
}

/**
 * Move a temporary block and set referencer and identifier numbers.
 * @param board
 * @param blockIndex
 * @param direction
 * @return moved block
 */
Board Solver::createMovedInstance(Board board, int blockIndex, int direction) {
    Board tempBoard;
    tempBoard = board;

    // Move the block
    tempBoard.moveBlock(blockIndex, direction);

    // Set the identifier to a random number while setting the referrer to the previous board's identifier.
    tempBoard.identifier = tempBoard.getHash();
    tempBoard.referrer = board.identifier;

    return tempBoard;
}

/**
 * Base solution for both BFS and DFS.
 * @param algorithm
 */
void Solver::solve(int algorithm) {
    Board board;

    // Loop over the queue until either the queue is empty or the solution is found.
    while (!this->boards.empty()) {

        // Get the next board and remove it from the list.
        board = this->boards.front();
        this->boards.pop_front();

        // Check if the board is solved completely.
        if (board.isCompleted()) {

            // The board is completed construct the solution steps.
            this->boards.clear();
            this->constructSolutionSteps(board);
            return;
        } else {
            Board tempBoard;

            // Construct the possible movement boards and push to the queue.
            for (int i = 0; i < board.blocks.size(); ++i) {
                if (board.blocks[i].isHorizontal()) {
                    for (int j = LEFT; j <= RIGHT; ++j) {
                        // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = this->createMovedInstance(board, i, j);
                            if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                                if (algorithm == BFS) {
                                    this->boards.push_back(tempBoard);
                                } else {
                                    this->boards.push_front(tempBoard);
                                }
                            }
                        }
                    }
                } else {
                    for (int j = UP; j <= DOWN; ++j) {
                        // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                        if (board.canMove(board.blocks[i], j)) {
                            tempBoard = this->createMovedInstance(board, i, j);
                            if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                                if (algorithm == BFS) {
                                    this->boards.push_back(tempBoard);
                                } else {
                                    this->boards.push_front(tempBoard);
                                }
                            }
                        }
                    }
                }
            }
        }

        // Move the board to the past steps.
        this->pastSteps[board.identifier] = board;
    }
}
