#include <iostream>
#include <string>
#include <regex>
#include <windows.h>

#include "settings.hpp"
#include "processInfo.cpp"

using namespace std;

activeWindowData previousData;

void formatOutput(string& text, activeWindowData data) {

    int idx = 0;

    while (text.find('%') != string::npos) {

        idx = text.find('%', idx);

        string temp = text.substr(idx, 4);

        if      (temp == "%pid")    text.replace(idx, 4, to_string(data.pid));
        else if (temp == "%nam")    text.replace(idx, 5, data.time);
        else if (temp == "%tim")    text.replace(idx, 5, data.name);
        else if (temp == "%pna")    text.replace(idx, 6, data.pname);
        else break;
        
    }


}

bool getWindowTitleData(string& title, string format, string& file, string& project) {

    string regexString = format;
    
    regexString = regex_replace(regexString, regex(R"(%file)"), "(.*?)");
    regexString = regex_replace(regexString, regex(R"(%project)"), "(.*?)"); 

    cout << regexString << " ";

    smatch matches;

    if (regex_search(title, matches, regex(regexString))) {
        
        if (matches.size() == 3) {

            if (format.find("%file") < format.find("%project")) {
                file = matches[1].str();
                project = matches[2].str();
            } else {
                file = matches[1].str();
                project = matches[2].str();
            }

            return true;

        } else if (matches.size() == 2) {

            if (format.find("%file") != string::npos) {
                file = matches[1].str();
            } else if (format.find("%project") != string::npos) {
                project = matches[1].str();
            }

            return true;
        }
    }
    return false;

}

int main() {
    // HWND hwnd = GetConsoleWindow();
    // ShowWindow(hwnd, SW_HIDE);


    cout << windowStartup << endl;


    while (true) {
        
        HWND target = GetForegroundWindow();

        // Get the window title

        char titleBuffer[256];
        GetWindowTextA(target, titleBuffer, 256);
        string title(titleBuffer);

        string file, project;

        // Acquire the application name, time and PID
        activeWindowData data = fetchWindowInfo(target);

        getWindowTitleData(title, titleFormats[data.pname], file, project);
        
        string a = format;
        formatOutput(a, data);

        /* Check if the PID is not equal to the previously acquired PID
            so the output is only printed when the window changes */

        if (data.name != "") cout << file << " " << project << endl;
        previousData = data;

        Sleep(interval);

    }

    return 0;
}
