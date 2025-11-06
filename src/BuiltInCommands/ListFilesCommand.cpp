#include "BuiltInCommands/ListFilesCommand.hpp"
#include <fmt/base.h>
#include <fmt/format.h>

#include "LittleShell.hpp"
#include "Log.hpp"

namespace Ls
{
    ListFilesCommand::ListFilesCommand(LittleShell& shell): BuiltInCommand(shell)
    {
    }

    bool ListFilesCommand::Execute(const std::vector<std::string>& arguments)
    {
        try
        {
            std::vector<std::string> directories;
            std::vector<std::string> files;
            std::vector<std::string> others;
            std::string path = arguments.empty() ? "." : arguments[0];
                
            for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path))
            {
                std::string fileName = entry.path().filename().string();
                if (entry.is_directory())
                    directories.push_back(fileName);
                else if (entry.is_regular_file())
                    files.push_back(fileName);
                else
                    others.push_back(fileName);
            }

            fmt::print("\n");
            auto printEntries = [](const std::vector<std::string>& fileNames, const std::string& suffix = "") {
                for (const std::string& fileName : fileNames)
                    fmt::print("{}{}\n", fileName, suffix);
            };
            
            printEntries(directories, "/");
            printEntries(files);
            printEntries(others);
            
            fmt::print("\n");
        }
        catch (const std::exception& e)
        {
            Log::LogError(fmt::format("List Files command failed:\n {}\n", e.what()));
            return false;
        }
        catch (...)
        {
            Log::LogError("List Files command failed:\n Unknown exception.\n");
            return false;
        }

        return true;
    }
}


