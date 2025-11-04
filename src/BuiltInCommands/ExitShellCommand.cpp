#pragma once
#include "BuiltInCommands/ExitShellCommand.hpp"

#include "LittleShell.hpp"

namespace Ls
{
    ExitShellCommand::ExitShellCommand(LittleShell& shell): BuiltInCommand(shell)
    {
    }

    bool ExitShellCommand::Execute(const std::vector<std::string>& arguments)
    {
        m_shell.SetIsRunning(false);
        return true;
    }
}


