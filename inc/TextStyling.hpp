#pragma once
#include <string>


namespace Ls::TextStyling
{
    // Colors
    constexpr std::string_view Black = "\033[30m";
    constexpr std::string_view Red = "\033[31m";
    constexpr std::string_view Green = "\033[32m";
    constexpr std::string_view Yellow = "\033[33m";
    constexpr std::string_view Blue = "\033[34m";
    constexpr std::string_view Magenta = "\033[35m";
    constexpr std::string_view Cyan = "\033[36m";
    constexpr std::string_view White = "\033[37m";
    
    // TextStyles
    constexpr std::string_view Bold = "\033[1m";
    constexpr std::string_view Dim = "\033[2m";
    constexpr std::string_view Italic = "\033[3m";
    constexpr std::string_view Underline = "\033[4m";
    constexpr std::string_view Blink = "\033[5m";
    constexpr std::string_view Reverse = "\033[7m";
    constexpr std::string_view Hidden = "\033[8m";
    
    // Reset
    constexpr std::string_view Reset = "\033[0m";
}


