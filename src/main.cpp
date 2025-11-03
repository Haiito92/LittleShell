#include <iostream>
#include "fmt/format.h"


int main(int argc, char** argv) {

    bool isRunning = true;
    while (isRunning)
    {
        fmt::print("LittleShell>");
        std::string input;
        std::getline(std::cin, input);
    }
    
    return 0;
}
