#ifndef UNBLOCK_ME_SOLVER_SOLVER_H
#define UNBLOCK_ME_SOLVER_SOLVER_H

#include <deque>
#include <map>
#include <queue>
#include "globals.h"
#include "Board.h"

class Solver {
public:
    Solver(const Board board);

    size_t numberOfNodes = 0;
    map<string, Board> pastSteps;
    vector<Board> steps;
    Board board;

    void solve(int algorithm);
private:

    void constructSolutionSteps(Board board);

    Board createMovedInstance(Board board, int blockIndex, int direction);

    void solveBFS();
    void solveDFS();
    void solveDijkstra();
};


#endif //UNBLOCK_ME_SOLVER_SOLVER_H
