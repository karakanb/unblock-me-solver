#include <iostream>
#include <fstream>
#include "Board.h"
#include "globals.h"

using namespace std;


int main() {

    ifstream dataFile(DATA_FILE_NAME);

    Board board;
    board.printBoard();
    board.populateBoard(dataFile);
    board.printBoard();
    return 0;
}