#include "LittleShell.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fmt/base.h>
#include <windows.h>
#include "BuiltInCommands/ChangeDirectoryCommand.hpp"
#include "BuiltInCommands/ExitShellCommand.hpp"
#include "BuiltInCommands/ListFilesCommand.hpp"

namespace Ls
{
    LittleShell::LittleShell():
    m_currentPath(std::filesystem::current_path().string()),
    m_builtInCommandExecutor(),
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
            
            // Process built in command
            if (m_builtInCommandExecutor.ExecuteBuiltInCommand(commandToken, arguments)) continue;

            // Process external command
            if (ProcessExternalCommand(input)) continue;

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

    bool LittleShell::ProcessExternalCommand(const std::string& input) const
    {
        // Setup for Windows process creation
        STARTUPINFOA startupInfo;
        PROCESS_INFORMATION processInfo;

        ZeroMemory(&startupInfo, sizeof(startupInfo));
        startupInfo.cb = sizeof(startupInfo);
        ZeroMemory(&processInfo, sizeof(processInfo));

        std::vector<char> commandLine(input.begin(), input.end());
        commandLine.push_back('\0');
        
        // Create process
        // Create the process
        if (!CreateProcessA(
                NULL,                 // Application name
                commandLine.data(),   // Command line
                NULL,                 // Process handle not inheritable
                NULL,                 // Thread handle not inheritable
                FALSE,                // Set handle inheritance to FALSE
                0,                    // No creation flags
                NULL,                 // Use parent's environment block
                NULL,                 // Use parent's starting directory
                &startupInfo,         // Pointer to STARTUPINFO structure
                &processInfo)         // Pointer to PROCESS_INFORMATION structure
        )
        {
            return false;
        }

        // Wait until the process exits
        WaitForSingleObject(processInfo.hProcess, INFINITE);

        // Get exit code
        DWORD exitCode;
        GetExitCodeProcess(processInfo.hProcess, &exitCode);
        // We maybe should do something with the exit code, a print ?

        // Close process and thread handles
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        
        return true;
    }
}
