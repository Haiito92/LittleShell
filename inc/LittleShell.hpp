#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "BuiltInCommandExecutor.hpp"
#include "ExternalCommandExecutor.hpp"
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
        
        std::string m_currentPath;
        BuiltInCommandExecutor m_builtInCommandExecutor;
        ExternalCommandExecutor m_ExternalCommandExecutor;
        bool m_isRunning;
    };
}


