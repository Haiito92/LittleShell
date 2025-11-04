#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace Ls
{
    class LittleShell;
    
    class BuiltInCommand
    {
    public:
        BuiltInCommand(LittleShell& shell);
        virtual ~BuiltInCommand() = default;
        virtual bool Execute(const std::vector<std::string>& arguments) = 0;

    protected:
        LittleShell& m_shell;
    };
}


