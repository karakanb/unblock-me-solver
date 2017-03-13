#include <fstream>
#include <cstring>
#include "Board.h"
#include "Solver.h"

using namespace std;
void errorOutput();

int main(int argc, char *argv[]) {

    // Do not execute if the number of parameters are wrong.
    if (argc != 4) {
        errorOutput();
        return 0;
    }

    srand(time(NULL));

    // Open the files.
    int algorithm = 0;
    if(strcmp(argv[1], "bfs") == 0) {
        algorithm = BFS;
    } else if(strcmp(argv[1], "dfs") == 0) {
        algorithm = DFS;
    } else {
        errorOutput();
        return -1;
    }

    ifstream inputFile(argv[2]);
    ofstream outputFile(argv[3]);

    try {
        Board board;
        board.populateBoard(inputFile);
        inputFile.close();
        printSeperator();
        board.print("Initial board state:\n");

        Solver solution(board);
        solution.solve(algorithm);

        printSeperator();
        pp("Puzzle is solved.");
        pp2("Number of steps to solve: ", solution.steps.size());
        printSeperator();

        int i = 0;
        for (vector<Board>::reverse_iterator it = solution.steps.rbegin(); it != solution.steps.rend(); ++it) {
            it->print("Step " + to_string(i) + "\n");
            i++;
        }

        pp("\n\nBittiiiii.\n\n");

        return 0;
    } catch (string errorMessage) {
        cerr << errorMessage << endl;
        return -1;
    }
}

void errorOutput() {
    cerr << endl << endl << "============================================================" << endl;
    cerr <<
         "Error: You need to provide the algorithm to solve the problem (bfs or dfs) with the names of the "
                 "input and output files." << endl;
    cerr << "============================================================" << endl << endl;
}