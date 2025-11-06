#include "LittleShell.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fmt/base.h>
#include "BuiltInCommands/ChangeDirectoryCommand.hpp"
#include "BuiltInCommands/ExitShellCommand.hpp"
#include "BuiltInCommands/ListFilesCommand.hpp"

namespace Ls
{
    LittleShell::LittleShell():
    m_currentPath(std::filesystem::current_path().string()),
    m_builtInCommandExecutor(),
    m_externalCommandExecutor(),
    m_isRunning(false)
    {
        m_builtInCommandExecutor.RegisterBuiltInCommand("cd", std::make_unique<ChangeDirectoryCommand>(*this));
        m_builtInCommandExecutor.RegisterBuiltInCommand("ls", std::make_unique<ListFilesCommand>(*this));
        m_builtInCommandExecutor.RegisterBuiltInCommand("exit", std::make_unique<ExitShellCommand>(*this));
    }

    void LittleShell::Run()
    {
        fmt::print("\nWelcome to LittleShell!\n"
                   "Made by: Antoine Hanna - Haiito92\n"
                   "https://github.com/Haiito92\n\n");
        
        m_isRunning = true;
        while (m_isRunning)
        {
            // Print location
            fmt::print("LS {}> ", m_currentPath);

            //Get user input
            std::string input;
            if (!std::getline(std::cin, input))
            {
                break;
            }

            if (input.empty()) continue;
            
            // Deconstruct into tokens for built-ins
            std::vector<std::string> tokens = DeconstructUserInput(input);

            std::string commandToken = tokens[0];
            std::vector<std::string> arguments = std::vector<std::string>(tokens.begin() + 1, tokens.end());
            
            // Try execute built in command - if found one, continue
            if (m_builtInCommandExecutor.ExecuteBuiltInCommand(commandToken, arguments)) continue;

            // Try execute external command - if found one, continue
            if (m_externalCommandExecutor.ExecuteExternalCommand(input)) continue;

            // Else: show error or debug in the terminal
        }

        fmt::print("\nThank you for using LittleShell!\nBye bye! :D\n\n");
    }

    void LittleShell::SetCurrentPath(std::string newPath)
    {
        m_currentPath = std::move(newPath);
    }

    void LittleShell::SetIsRunning(bool newValue)
    {
        m_isRunning = newValue;
    }

    std::vector<std::string> LittleShell::DeconstructUserInput(const std::string& input) const
    {
        std::istringstream iss(input);
        std::string token;
        std::vector<std::string> tokens;

        while (iss >> token)
        {
            tokens.push_back(token);
        }

        return tokens;
    }
}
