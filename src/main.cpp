#include <fstream>
#include <cstring>
#include <chrono>
#include "Board.h"
#include "Solver.h"

using namespace std;

void errorOutput(string errorMessage = "");

int main(int argc, char *argv[]) {

    // Do not execute if the number of parameters are wrong.
    if (argc != 4) {
        errorOutput();
        return 0;
    }

    srand(time(NULL));

    // Open the files.
    int algorithm = 0;
    if (strcmp(argv[1], "bfs") == 0) {
        algorithm = BFS;
    } else if (strcmp(argv[1], "dfs") == 0) {
        algorithm = DFS;
    } else {
        errorOutput();
        return -1;
    }

    ifstream inputFile(argv[2]);
    if (!inputFile.is_open()) {
        errorOutput("There was a problem with the input file, please verify that the input file is there.");
        return -1;
    }

    ofstream outputFile(argv[3]);
    if (!outputFile.is_open()) {
        errorOutput("There was a problem with the output file, please verify that the output file is there.");
        return -1;
    }

    try {
        // Create and populate the board from the input file.
        Board board;
        board.populateBoard(inputFile);

        // Print the initial state of the board.
        printSeperator();
        board.print("Initial board state:\n");


        // Record start time
        auto start = chrono::high_resolution_clock::now();

        // Solve the board with the algorithm provided.
        Solver solution(board);
        solution.solve(algorithm);

        // Record end time
        auto finish = chrono::high_resolution_clock::now();

        printSeperator();
        pp("Puzzle is solved.");
        pp2("Number of steps to solve: ", solution.steps.size());
        printSeperator();

        int i = 0;
        for (vector<Board>::reverse_iterator it = solution.steps.rbegin(); it != solution.steps.rend(); ++it) {

            // Print the board to the screen.
            it->print("Step " + to_string(i) + "\n");

            // Export the board state to the output file.
            it->exportToFile(outputFile);

            // Set the spacing between different board states in the file.
            outputFile << endl << endl;
            i++;
        }

        printSeperator();
        std::chrono::duration<double> runningTime = finish - start;
        pp("The puzzle is solved.");
        pp2("The total time in seconds the algorithm took to solve the puzzle: ", runningTime.count());
        pp2("The total number of boards seen to find the solution including the initial state: ",
            solution.numberOfNodes);
        pp("The block with 1s represent the block which is asked to be rescued.");
        pp("The output states are written to the output file you provided.");
        printSeperator();

        inputFile.close();
        outputFile.close();
        return 0;
    } catch (string errorMessage) {
        cerr << errorMessage << endl;
        return -1;
    }
}

/**
 * Output an error with the given optional message and keep a basic error styling.
 * @param errorMessage
 */
void errorOutput(string errorMessage) {
    cerr << endl << endl << "============================================================" << endl;
    if (errorMessage.compare("") == 0) {
        cerr <<
             "Error: You need to provide the algorithm to solve the problem (bfs or dfs) with the names of the "
                     "input and output files." << endl;
    } else {
        cerr << errorMessage << endl;
    }
    cerr << "============================================================" << endl << endl;
}