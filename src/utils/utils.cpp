#include "../../include/utils/utils.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace Utils {

    void clearScreen() {
#ifdef _WIN32
        // For Windows
        system("cls");
#else
        // For Unix/Linux/MacOS
        std::cout << "\033[2J\033[1;1H";
#endif
    }

    void printSeparatorLine() {
        std::cout << std::string(50, '-') << std::endl;
    }

}