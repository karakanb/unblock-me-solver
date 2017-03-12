//
// Created by burak on 11.03.2017.
//

#ifndef UNLOCK_ME_SOLVER_SOLVER_H
#define UNLOCK_ME_SOLVER_SOLVER_H

#include <deque>
#include <set>
#include "globals.h"
#include "Board.h"

class Solver {
public:
    Solver(const Board board);

    vector<Board> pastSteps;
    deque<Board> boards;
    vector<Board> steps;
    void withBFS();
    void withDFS();

private:
    void constructSolutionSteps(Board board);
};


#endif //UNLOCK_ME_SOLVER_SOLVER_H
