#pragma once
#include <string>


namespace Ls::TextStyling
{
    // Colors
    constexpr std::string Black = "\033[30m";
    constexpr std::string Red = "\033[31m";
    constexpr std::string Green = "\033[32m";
    constexpr std::string Yellow = "\033[33m";
    constexpr std::string Blue = "\033[34m";
    constexpr std::string Magenta = "\033[35m";
    constexpr std::string Cyan = "\033[36m";
    constexpr std::string White = "\033[37m";

    // TextStyles
    constexpr std::string Bold = "\033[1m";
    constexpr std::string Dim = "\033[2m";
    constexpr std::string Italic = "\033[3m";
    constexpr std::string Underline = "\033[4m";
    constexpr std::string Blink = "\033[5m";
    constexpr std::string Reverse = "\033[7m";
    constexpr std::string Hidden = "\033[8m";

    // Reset
    constexpr std::string Reset = "\033[0m";
}


