#pragma once
#include <string>
#include <vector>

#include "BuiltInCommand.hpp"

namespace Ls
{
    class ListFilesCommand : public BuiltInCommand
    {
    public:
        ListFilesCommand(LittleShell& shell);
        virtual bool Execute(const std::vector<std::string>& arguments) override;
    };
}


