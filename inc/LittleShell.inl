#pragma once

namespace Ls
{
    template <typename T>
    void LittleShell::BindBuiltInCommand(const std::string& commandName, T* object, BuiltInCommandMethod<T> method)
    {
        if (!object) throw std::invalid_argument("LittleShell::BindBuiltInCommand() : object is nullptr");   
        if (!method) throw std::invalid_argument("LittleShell::BindBuiltInCommand() : method is nullptr");

        BuiltInCommandLambda lambda = [object, method](const std::vector<std::string>& arguments) -> bool
        {
            return (object->*method)(arguments);
        };

        m_builtInCommands[commandName] = std::move(lambda);
    }
}


