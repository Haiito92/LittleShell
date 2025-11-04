#include "LittleShell.hpp"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <fmt/base.h>

namespace Ls
{
    LittleShell::LittleShell():
    m_currentPath(std::filesystem::current_path()),
    m_builtInCommands()
    {
        BindBuiltInCommands();
    }

    void LittleShell::Run()
    {
        fmt::print("Welcome to LittleShell !\n");
        
        bool isRunning = true;
        while (isRunning)
        {
            // Print location
            fmt::print("LS {}>", m_currentPath.string());

            // Get Tokens from user input - GetTokensFromUserInput calls getline so it blocks the program,
            // waiting for the user to press enter 
            std::vector<std::string> tokens = GetUserInput();

            if (tokens.empty()) continue;

            std::string commandToken = tokens[0];
            std::vector<std::string> arguments = std::vector<std::string>(tokens.begin() + 1, tokens.end());
            
            // Process built in command
            if (ProcessBuiltInCommand(commandToken, arguments)) continue;

            // Process external command
            
        }

        fmt::print("Exiting LittleShell !\n");
    }

    void LittleShell::BindBuiltInCommands()
    {
        BindBuiltInCommand("cd", this, &LittleShell::ChangeDirectory);
    }

    std::vector<std::string> LittleShell::GetUserInput() const
    {
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::string token;
        std::vector<std::string> tokens;

        while (iss >> token)
        {
            tokens.push_back(token);
        }

        return tokens;
    }

    
    bool LittleShell::ProcessBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments)
    {
        for (const auto& command : m_builtInCommands)
        {
            if (command.first == commandToken)
            {
                // Right now we don't do anything with the return of the command
                command.second(arguments);
                return true; // We return true because we were able to call a built-in command, it's result doesn't matter.
            }
        }
        
        return false;
    }

    bool LittleShell::ProcessExternalCommand(const std::string& commandToken, const std::vector<std::string>& arguments) const
    {
        return true;
    }

    bool LittleShell::ChangeDirectory(const std::vector<std::string>& arguments)
    {
        if (arguments.empty()) return false;

        try
        {
            std::filesystem::current_path(arguments[0]);
            m_currentPath = std::filesystem::current_path(); 
        }
        catch (...)
        {
            return false;
        }
        
        return true;
    }
}
