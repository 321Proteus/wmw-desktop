#include <iostream>
#include <string>
#include <windows.h>

#include "settings.hpp"
#include "processInfo.cpp"

using namespace std;

activeWindowData previousData;

void formatOutput(string& text, activeWindowData data) {

    int idx = 0;

    while (text.find('%') != string::npos) {

        idx = text.find('%', idx);
        
        switch (text[idx+1]) {
            case 'n': text.replace(idx, 5, data.name); break;
            case 't': text.replace(idx, 5, data.time); break;
            case 'p': text.replace(idx, 4, to_string(data.pid)); break;
            default: break;
        }
    }


}

int main() {
    // HWND hwnd = GetConsoleWindow();
    // ShowWindow(hwnd, SW_HIDE);


    cout << windowStartup << endl;


    while (true) {
        
        HWND target = GetForegroundWindow();

        // Acquire the application name, time and PID
        activeWindowData data = fetchWindowInfo(target);

        string a = format;
        formatOutput(a, data);

        /* Check if the PID is not equal to the previously acquired PID
            so the output is only printed when the window changes */

        if (data.name != "") cout << a << endl;
        previousData = data;

        Sleep(interval);

    }

    return 0;
}
