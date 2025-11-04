#include "LittleShell.hpp"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <fmt/base.h>
#include <windows.h>

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
        fmt::print("Welcome to LittleShell!\n");
        
        m_isRunning = true;
        while (m_isRunning)
        {
            // Print location
            fmt::print("LS {}> ", m_currentPath.string());

            //Get user input
            std::string input;
            if (!std::getline(std::cin, input))
            {
                m_isRunning = false;
                break;
            }

            if (input.empty()) continue;
            
            // Deconstruct into tokens for built-ins
            std::vector<std::string> tokens = DeconstructUserInput(input);

            std::string commandToken = tokens[0];
            std::vector<std::string> arguments = std::vector<std::string>(tokens.begin() + 1, tokens.end());
            
            // Process built in command
            if (ProcessBuiltInCommand(commandToken, arguments)) continue;

            // Process external command (not using return right now)
            ProcessExternalCommand(input);
        }

        fmt::print("\nThank you for using LittleShell!\nBye bye! :D\n");
    }

    void LittleShell::BindBuiltInCommands()
    {
        BindBuiltInCommand("cd", this, &LittleShell::ChangeDirectory);
        BindBuiltInCommand("exit", this, &LittleShell::ExitShell);
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

    bool LittleShell::ExitShell(const std::vector<std::string>& arguments)
    {
        m_isRunning = false;
        return true;
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
