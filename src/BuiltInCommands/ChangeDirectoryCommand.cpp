#include "BuiltInCommands/ChangeDirectoryCommand.hpp"
#include "LittleShell.hpp"

namespace Ls
{
    ChangeDirectoryCommand::ChangeDirectoryCommand(LittleShell& shell): BuiltInCommand(shell)
    {
    }

    bool ChangeDirectoryCommand::Execute(const std::vector<std::string>& arguments)
    {
        if (arguments.empty()) return false;

        try
        {
            std::filesystem::current_path(arguments[0]);
            m_shell.SetCurrentPath(std::filesystem::current_path().string()); 
        }
        catch (...)
        {
            return false;
        }
        
        return true;
    }
}


