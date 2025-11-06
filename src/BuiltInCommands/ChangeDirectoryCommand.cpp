#include "BuiltInCommands/ChangeDirectoryCommand.hpp"

#include <fmt/format.h>

#include "LittleShell.hpp"
#include "Log.hpp"

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
        catch (std::exception& e)
        {
            Log::LogError(fmt::format("Change Directory command failed:\n {}", e.what()));
            return false;
        }
        catch (...)
        {
            Log::LogError("Change Directory command failed:\n Unknown exception.");
            return false;
        }
        
        return true;
    }
}


