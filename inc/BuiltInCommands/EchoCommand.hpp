#pragma once
#include <filesystem>
#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

namespace Ls
{
    class ExitShellCommand : public BuiltInCommand
    {
    public:
        ExitShellCommand(LittleShell& shell);
        virtual bool Execute(const std::vector<std::string>& arguments) override;
    };
}


