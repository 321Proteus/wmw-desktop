#include <windows.h>
#include <string>
#include <time.h>
#include <psapi.h>
#include <iterator>
#include "settings.hpp"

using namespace std;

activeWindowData fetchWindowInfo(HWND window) {

    time_t startTime = time(nullptr);
    activeWindowData info;
    unsigned int s, m, h;


    // Acquire the Process Identifier - to open the process handle
    DWORD pid;
    GetWindowThreadProcessId(window, &pid);

    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);


    // Acquire the executable path - it will be needed to identify the program
    char filePath[MAX_PATH];
    GetModuleFileNameExA(processHandle, nullptr, filePath, MAX_PATH);
    string fullPath(filePath);

    // Cut off the executable name from the path
    string processName = fullPath.substr(fullPath.find_last_of("\\") + 1);


    /* Initialize four variables - only createTime will be used,
    but for some reason using null pointers didn't work here for me */
    FILETIME createTime, exitTime, kernelTime, userTime;

    /* Calculate the elapsed time by subtracting the process time from the start time,
    convert it to seconds and write to the seconds buffer */
    if (GetProcessTimes(processHandle, &createTime, &exitTime, &kernelTime, &userTime)) {

        CloseHandle(processHandle);

        ULARGE_INTEGER appTime;
        appTime.LowPart = createTime.dwLowDateTime;
        appTime.HighPart = createTime.dwHighDateTime;

        time_t elapsed = static_cast<time_t>(appTime.QuadPart / 10000000ULL - 11644473600ULL);

        s = abs(static_cast<int>(difftime(time(nullptr), startTime) - difftime(time(nullptr), elapsed)));
    }
    CloseHandle(processHandle);


    // Converting elapsed seconds to "HH:MM:SS" format
    h = s / 3600;
    m = (s % 3600) / 60;
    s = s % 60;

    char formattedTime[9];
    sprintf(formattedTime, "%02d:%02d:%02d", h, m, s);

    string appName = "";
    // Check if the executable appears on the code editor list
    map<string, string>::iterator i;

    for (i = codeEditors.begin(); i != codeEditors.end(); i++) {
        // executable is a code editor
        if (processName == i->first)
            appName = i->second;
    }
    // If the app is not a code editor, leave it blank, it will be handled later

    // Copying fetched values into the return structure
    info.pid = int(pid);
    info.name = appName;
    info.time = string(formattedTime);
    info.pname = processName;

    return info;
}
