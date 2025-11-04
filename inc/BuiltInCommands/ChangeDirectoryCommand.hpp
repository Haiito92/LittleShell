#pragma once
#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

namespace Ls
{
    class ChangeDirectoryCommand : public BuiltInCommand
    {
    public:
        ChangeDirectoryCommand(LittleShell& shell);
        virtual bool Execute(const std::vector<std::string>& arguments) override;
    };
}


