#include <fstream>
#include "Board.h"

using namespace std;


int main() {

    ifstream dataFile(DATA_FILE_NAME);

    try {
        Board board;
        board.print();
        board.populateBoard(dataFile);
        board.print();
        board.blocks.pop_back();
        board.moveBlock(board.blocks.back(), UP);
        board.print();
        return 0;
    } catch (const char * errorMessage) {
        cerr << errorMessage << endl;
        return -1;
    }
}