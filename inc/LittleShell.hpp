#pragma once
#include <string>
#include <vector>

namespace Ls
{
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

        bool ProcessBuiltInCommand(const std::string& commandToken, const std::vector<std::string>& arguments);
        bool ProcessExternalCommand(const std::string& commandToken, const std::vector<std::string>& arguments);

    private:
        
    };
}


