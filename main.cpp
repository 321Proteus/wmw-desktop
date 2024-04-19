#include <iostream>
#include <string>
#include <windows.h>

#include "settings.hpp"
#include "processInfo.cpp"

using namespace std;

activeWindowData previousData;

int main() {
    // HWND hwnd = GetConsoleWindow();
    // ShowWindow(hwnd, SW_HIDE);


    cout << windowStartup << endl;


    while (true) {
        
        HWND target = GetForegroundWindow();

        // Acquire the application name, time and PID
        activeWindowData data = fetchWindowInfo(target);
        string fullData = data.name + " " + data.time;

        /* Check if the PID is not equal to the previously acquired PID
            so the output is only printed when the window changes */

        if (data.name != "") cout << fullData << endl;
        previousData = data;

        Sleep(interval);

    }

    return 0;
}
