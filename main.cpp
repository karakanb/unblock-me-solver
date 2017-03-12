#include <fstream>
#include "Board.h"
#include "Solver.h"

using namespace std;

int main() {

    srand(time(NULL));

    ifstream dataFile(DATA_FILE_NAME);

    try {
        Board board;

        board.populateBoard(dataFile);
        board.print();

        dataFile.close();

        Solver solver(board);
        solver.withBFS();

        pp("===========================");
        pp2("Count: ", solver.steps.size());
        for (vector<Board>::iterator it = solver.steps.begin(); it != solver.steps.end(); ++it) {
            it->print();
        }

        pp("\n\nBittiiiii.\n\n");

        return 0;
    } catch (string errorMessage) {
        cerr << errorMessage << endl;


        return -1;
    } catch (const char *m) {
        cerr << m << endl;
        return -1;
    }
}