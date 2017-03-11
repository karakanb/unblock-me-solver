#ifndef HW1_GLOBALS_H
#define HW1_GLOBALS_H

#include <iostream>
#include <string>

#define DATA_FILE_NAME "blocks.txt"
#define BOARD_SIZE 6
#define HORIZONTAL 0
#define VERTICAL 1
#define ESCAPE_X 3
#define ESCAPE_Y 6

#define pp(x)  cout << x << endl;

enum {
    LEFT, RIGHT, UP, DOWN
};

inline void throwError(const char *errorMessage) {
    std::string errorString(errorMessage);
    std::cout << errorString << std::endl;
    std::string seperator("\n   \n===========================\n\n");
    errorString = seperator + errorString + seperator;
    std::cout << errorString << std::endl;
    throw errorString;
}


#endif //HW1_GLOBALS_H
