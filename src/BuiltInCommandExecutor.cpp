#include "BuiltInCommandExecutor.hpp"

namespace Ls
{
    BuiltInCommandExecutor::BuiltInCommandExecutor():
    m_builtInCommands()
    {
    }

    void BuiltInCommandExecutor::RegisterBuiltInCommand(const std::string& commandToken, std::unique_ptr<BuiltInCommand> builtInCommand)
    {
        m_builtInCommands[commandToken] = std::move(builtInCommand);
    }

    bool BuiltInCommandExecutor::ExecuteBuiltInCommand(const std::string& commandToken,
        const std::vector<std::string>& arguments)
    {
        auto it = m_builtInCommands.find(commandToken);
        if (it == m_builtInCommands.end()) return false;

        // For now we don't use the return of the execute of the command.
        // We just return true to tell we found and executed a command (even if execution failed).
        it->second->Execute(arguments);
        return true;
    }
}
