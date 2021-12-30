#include "Solver.h"

/**
 * Base constructor that pushes the root node to the double-ended queue.
 * @param board
 * @return
 */
Solver::Solver(Board board) {
    this->board = board;
}

/**
 * Construct the solution steps from the pastSteps vector by using the reference chain.
 * @param board
 */
void Solver::constructSolutionSteps(Board board) {

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
 * Move a temporary block and set reference and identifier numbers.
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

    // Set the identifier to a unique hash while setting the referrer to the previous board's identifier.
    tempBoard.identifier = tempBoard.getHash();
    tempBoard.referrer = board.identifier;

    return tempBoard;
}

/**
 * Base solution for both BFS and DFS.
 * @param algorithm
 */
void Solver::solve(int algorithm) {
    if (algorithm == BFS) {
        this->solveBFS();
    } else if (algorithm == DFS) {
        this->solveDFS();
    } else {
        this->solveDijkstra();
    }
}

void Solver::solveBFS() {
    deque<Board> boards;
    boards.push_back(this->board);

    // Loop over the queue until either the queue is empty or the solution is found.
    while (!boards.empty()) {

        // Get the next board and remove it from the list.
        Board board = boards.front();
        boards.pop_front();

        // Check if the board is solved completely.
        if (board.isCompleted()) {

            // The board is completed construct the solution steps.
            this->constructSolutionSteps(board);
            return;
        }

        // Construct the possible movement boards and push to the queue.
        for (int i = 0; i < board.blocks.size(); ++i) {
            if (board.blocks[i].isHorizontal()) {
                for (int j = LEFT; j <= RIGHT; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push_back(tempBoard);
                        }
                    }
                }
            } else {
                for (int j = UP; j <= DOWN; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push_back(tempBoard);
                        }
                    }
                }
            }
        }

        // Move the board to the past steps.
        this->pastSteps[board.identifier] = board;
    }
}

void Solver::solveDFS() {
    deque<Board> boards;
    boards.push_back(this->board);

    // Loop over the queue until either the queue is empty or the solution is found.
    while (!boards.empty()) {

        // Get the next board and remove it from the list.
        Board board = boards.front();
        boards.pop_front();

        // Check if the board is solved completely.
        if (board.isCompleted()) {

            // The board is completed construct the solution steps.
            this->constructSolutionSteps(board);
            return;
        }

        // Construct the possible movement boards and push to the queue.
        for (int i = 0; i < board.blocks.size(); ++i) {
            if (board.blocks[i].isHorizontal()) {
                for (int j = LEFT; j <= RIGHT; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push_front(tempBoard);
                        }
                    }
                }
            } else {
                for (int j = UP; j <= DOWN; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end()) {
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push_front(tempBoard);
                        }
                    }
                }
            }
        }

        // Move the board to the past steps.
        this->pastSteps[board.identifier] = board;
    }
}

void Solver::solveDijkstra() {
    map<string, unsigned> steps{};
    steps[this->board.identifier] = 0;
    auto cmp = [&](const Board& a, const Board& b) { return steps[a.identifier] > steps[b.identifier]; };
    priority_queue<Board, deque<Board>, decltype(cmp)> boards(cmp);
    boards.push(this->board);

    // Loop over the queue until either the queue is empty or the solution is found.
    while (!boards.empty()) {

        // Get the next board and remove it from the list.
        Board board = boards.top();
        boards.pop();

        // Check if the board is solved completely.
        if (board.isCompleted()) {

            // The board is completed construct the solution steps.
            this->constructSolutionSteps(board);
            return;
        }

        const unsigned step = steps[board.identifier];

        // Construct the possible movement boards and push to the queue.
        for (int i = 0; i < board.blocks.size(); ++i) {
            if (board.blocks[i].isHorizontal()) {
                for (int j = LEFT; j <= RIGHT; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end() || step + 1 < steps[tempBoard.identifier]) {
                            steps[tempBoard.identifier] = step + 1;
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push(tempBoard);
                        }
                    }
                }
            } else {
                for (int j = UP; j <= DOWN; ++j) {
                    // If the board can move, create the moved instance with appropriate referrer and identifier numbers.
                    if (board.canMove(board.blocks[i], j)) {
                        Board tempBoard = this->createMovedInstance(board, i, j);
                        if (this->pastSteps.find(tempBoard.identifier) == this->pastSteps.end() || step + 1 < steps[tempBoard.identifier]) {
                            steps[tempBoard.identifier] = step + 1;
                            this->pastSteps[tempBoard.identifier] = tempBoard;
                            boards.push(tempBoard);
                        }
                    }
                }
            }
        }

        // Move the board to the past steps.
        this->pastSteps[board.identifier] = board;
    }
}
