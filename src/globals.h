#ifndef UNBLOCK_ME_SOLVER_GLOBALS_H
#define UNBLOCK_ME_SOLVER_GLOBALS_H

#include <iostream>
#include <string>

#define BOARD_SIZE 6

#define HORIZONTAL 0
#define VERTICAL 1

#define pp(x)  cout << x << endl;
#define pp2(x, y)  cout << x << " " <<   y << endl;


enum {
    LEFT, RIGHT, UP, DOWN
};

enum {
    BFS, DFS
};

inline void printSeperator() {
    std::cout << std::endl << "===========================" << std::endl << std::endl;
}

inline void throwError(const char *errorMessage, int blockId = -1) {
    std::string errorString(errorMessage);
    std::string seperator("\n\n===========================\n\n");
    errorString = seperator + errorString;
    if (blockId != -1) {
        std::string blockMessage(" Block ID: ");
        errorString = errorString + blockMessage + std::to_string(blockId);
    }

    errorString += seperator;

    throw errorString;
}


#endif //UNBLOCK_ME_SOLVER_GLOBALS_H
