#pragma once
#include <filesystem>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Ls
{
    template<typename T>
    using BuiltInCommandMethod = bool(T::*)(const std::vector<std::string>&);
    using BuiltInCommandLambda = std::function<bool(const std::vector<std::string>&)>;
    
    class LittleShell
    {
    public:
        LittleShell();
        LittleShell(const LittleShell& other) = delete;
        LittleShell(LittleShell&& other) = delete;
        ~LittleShell() = default;

        LittleShell& operator=(const LittleShell& other) = delete;
        LittleShell& operator=(LittleShell&& other) = delete;

        void Run();

    private:
        void BindBuiltInCommands();
        template<typename T>
        void BindBuiltInCommand(const std::string& commandName, T* object, BuiltInCommandMethod<T> method);
        
        std::vector<std::string> DeconstructUserInput(const std::string& input) const;

        bool ProcessBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments);
        bool ChangeDirectory(const std::vector<std::string>& arguments);

        bool ProcessExternalCommand(const std::string& input) const;
        
        std::filesystem::path m_currentPath;
        std::unordered_map<std::string, BuiltInCommandLambda> m_builtInCommands;
    };
}

#include "LittleShell.inl"


