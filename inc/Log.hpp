#pragma once
#include <string>

namespace Ls::Log
{
    void LogInfo(const std::string& message);
    void LogWarning(const std::string& message);
    void LogError(const std::string& message);
    void Log(const std::string& message);
}


