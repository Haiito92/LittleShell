#include "Log.hpp"

#include <fmt/base.h>
#include <fmt/format.h>

#include "TextStyling.hpp"

namespace Ls::Log
{
    void LogInfo(const std::string& message)
    {
        Log(fmt::format("{}[LS INFO]: {}{}", TextStyling::Blue, message, TextStyling::Reset));
    }

    void LogWarning(const std::string& message)
    {
        Log(fmt::format("{}[LS WARNING]: {}{}", TextStyling::Yellow, message, TextStyling::Reset));
    }

    void LogError(const std::string& message)
    {
        Log(fmt::format("{}[LS ERROR]: {}{}", TextStyling::Red, message, TextStyling::Reset));
    }

    void Log(const std::string& message)
    {
        fmt::print("{}\n", message);
    }
}
