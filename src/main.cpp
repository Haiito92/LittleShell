#include <iostream>

#include "LittleShell.hpp"
#include "fmt/format.h"


int main(int argc, char** argv)
{

    try
    {
        Ls::LittleShell shell;
        shell.Run();
    }
    catch (const std::exception& e)
    {
        fmt::print("Catched standard exception:\n{}\n", e.what());    
    }
    catch (...)
    {
        fmt::print("Catched unknown exception\n");
    }
    
    return 0;
}
