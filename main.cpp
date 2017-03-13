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
        dataFile.close();
        board.print();

        Solver solver(board);
        solver.withBFS();

        pp("===========================");
        pp2("Count: ", solver.steps.size());
        for (vector<Board>::reverse_iterator it = solver.steps.rbegin(); it != solver.steps.rend(); ++it) {
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