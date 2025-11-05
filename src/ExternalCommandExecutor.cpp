#include "ExternalCommandExecutor.hpp"
#include <windows.h>

namespace Ls
{
    bool ExternalCommandExecutor::ExecuteExternalCommand(const std::string& input) const
    {
        // Setup for Windows process creation
        STARTUPINFOA startupInfo;
        PROCESS_INFORMATION processInfo;

        ZeroMemory(&startupInfo, sizeof(startupInfo));
        startupInfo.cb = sizeof(startupInfo);
        ZeroMemory(&processInfo, sizeof(processInfo));

        std::vector<char> commandLine(input.begin(), input.end());
        commandLine.push_back('\0');
        
        // Create process
        // Create the process
        if (!CreateProcessA(
                NULL,                 // Application name
                commandLine.data(),   // Command line
                NULL,                 // Process handle not inheritable
                NULL,                 // Thread handle not inheritable
                FALSE,                // Set handle inheritance to FALSE
                0,                    // No creation flags
                NULL,                 // Use parent's environment block
                NULL,                 // Use parent's starting directory
                &startupInfo,         // Pointer to STARTUPINFO structure
                &processInfo)         // Pointer to PROCESS_INFORMATION structure
        )
        {
            return false;
        }

        // Wait until the process exits
        WaitForSingleObject(processInfo.hProcess, INFINITE);

        // Get exit code
        DWORD exitCode;
        GetExitCodeProcess(processInfo.hProcess, &exitCode);
        // We maybe should do something with the exit code, a print ?

        // Close process and thread handles
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);

        // We return through even if the process failed or had an error.
        // Because the return here is only used to know if we found an external process or not.
        // Not to tell if it succeeded.
        return true;
    }
}
