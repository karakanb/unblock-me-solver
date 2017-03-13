#ifndef UNLOCK_ME_SOLVER_SOLVER_H
#define UNLOCK_ME_SOLVER_SOLVER_H

#include <deque>
#include <map>
#include "globals.h"
#include "Board.h"

class Solver {
public:
    Solver(const Board board);

    map<long, Board> pastSteps;
    deque<Board> boards;
    vector<Board> steps;

    void solve(int algorithm);
private:

    void constructSolutionSteps(Board board);

    Board createMovedInstance(Board board, int blockIndex, int direction);
};


#endif //UNLOCK_ME_SOLVER_SOLVER_H
