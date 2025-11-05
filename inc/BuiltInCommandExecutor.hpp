#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>
#include "BuiltInCommands/BuiltInCommand.hpp"

namespace Ls
{
    class BuiltInCommandExecutor
    {
    public:
        BuiltInCommandExecutor();
        BuiltInCommandExecutor(const BuiltInCommandExecutor& other) = delete;
        BuiltInCommandExecutor(BuiltInCommandExecutor&& other) = delete;
        ~BuiltInCommandExecutor() = default;

        BuiltInCommandExecutor& operator=(const BuiltInCommandExecutor& other) = delete;
        BuiltInCommandExecutor& operator=(BuiltInCommandExecutor&& other) = delete;

        void RegisterBuiltInCommand(const std::string& commandToken, std::unique_ptr<BuiltInCommand> builtInCommand);
        bool ExecuteBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments);
    private:
        std::unordered_map<std::string, std::unique_ptr<BuiltInCommand>> m_builtInCommands;
    };
}


