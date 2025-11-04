#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "BuiltInCommands/BuiltInCommand.hpp"

namespace Ls
{
    class BuiltInCommand;
    class LittleShell
    {
    public:
        LittleShell();
        LittleShell(const LittleShell& other) = delete;
        LittleShell(LittleShell&& other) = delete;
        ~LittleShell() = default;

        LittleShell& operator=(const LittleShell& other) = delete;
        LittleShell& operator=(LittleShell&& other) = delete;

        void Run();
        
        void SetCurrentPath(std::string newPath);
        void SetIsRunning(bool newValue);

    private:
        
        std::vector<std::string> DeconstructUserInput(const std::string& input) const;

        bool ProcessBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments);
        bool ProcessExternalCommand(const std::string& input) const;
        
        std::string m_currentPath;
        std::unordered_map<std::string, std::unique_ptr<BuiltInCommand>> m_builtInCommands;
        bool m_isRunning = false;
    };
}


