#ifndef UNBLOCK_ME_SOLVER_SOLVER_H
#define UNBLOCK_ME_SOLVER_SOLVER_H

#include <deque>
#include <map>
#include "globals.h"
#include "Board.h"

class Solver {
public:
    Solver(const Board board);

    unsigned long numberOfNodes = 0;
    map<string, Board> pastSteps;
    deque<Board> boards;
    vector<Board> steps;

    void solve(int algorithm);
private:

    void constructSolutionSteps(Board board);

    Board createMovedInstance(Board board, int blockIndex, int direction);
};


#endif //UNBLOCK_ME_SOLVER_SOLVER_H
