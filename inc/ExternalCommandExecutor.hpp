#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>

namespace Ls
{
    class ExternalCommandExecutor
    {
    public:
        ExternalCommandExecutor() = default;
        ExternalCommandExecutor(const ExternalCommandExecutor& other) = delete;
        ExternalCommandExecutor(ExternalCommandExecutor&& other) = delete;
        ~ExternalCommandExecutor() = default;

        ExternalCommandExecutor& operator=(const ExternalCommandExecutor& other) = delete;
        ExternalCommandExecutor& operator=(ExternalCommandExecutor&& other) = delete;

        bool ExecuteExternalCommand(const std::string& input) const;
    };
}


