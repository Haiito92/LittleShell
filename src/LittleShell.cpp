#include "LittleShell.hpp"
#include <iostream>
#include <sstream>
#include <fmt/base.h>

namespace Ls
{
    LittleShell::LittleShell()
    {
    }

    void LittleShell::Run()
    {
        fmt::print("Welcome to LittleShell !\n");
        
        bool isRunning = true;
        while (isRunning)
        {
            // Print location
            fmt::print("LittleShell>");

            std::string input;
            std::getline(std::cin, input);
            
            // Get user input as tokens
            std::stringstream inputStream(input);
            std::string token;
            std::vector<std::string> tokens;
            while (inputStream >> token)
            {
                tokens.push_back(token);
            }

            if (tokens.empty()) continue;

            std::string commandToken = tokens[0];
            std::vector<std::string> arguments = std::vector<std::string>(tokens.begin() + 1, tokens.end());
            
            // Process built in command
            if (ProcessBuiltInCommand(commandToken, arguments)) continue;

            // Process external command
            
        }

        fmt::print("Exiting LittleShell !\n");
    }

    bool LittleShell::ProcessBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments)
    {
        fmt::print("Command Token: {}\n", commandToken);
        return true;
    }

    bool LittleShell::ProcessExternalCommand(const std::string& commandToken, const std::vector<std::string>& arguments)
    {
        return true;
    }
}
