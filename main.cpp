#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <locale>

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

bool getWindowTitleData(wstring& title, wstring format, wstring& file, wstring& project) {

    wstring regexString = format;
    
    regexString = regex_replace(regexString, wregex(L"%file"), L"(.*?)");
    regexString = L"^" + regex_replace(regexString, wregex(L"%project"), L"(.*?)") + L"$"; 

    // wcout << regexString << L" ";

    wsmatch matches;

    if (regex_search(title, matches, wregex(regexString))) {
        
        if (matches.size() == 3) {

            if (format.find(L"%file") < format.find(L"%project")) {
                file = matches[1].str();
                project = matches[2].str();
            } else {
                file = matches[1].str();
                project = matches[2].str();
            }

            return true;

        } else if (matches.size() == 2) {

            if (format.find(L"%file") != string::npos) {
                file = matches[1].str();
            } else if (format.find(L"%project") != string::npos) {
                project = matches[1].str();
            }

            return true;
        }
    }
    return false;

}

int main() {

    _setmode(_fileno(stdout), 0x40000);

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);


    cout << windowStartup << endl;

    while (true) {
        
        HWND target = GetForegroundWindow();

        // Get the window title

        wchar_t titleBuffer[256]{};
        int y = GetWindowTextW(target, titleBuffer, 256);       

        wstring title(titleBuffer);

        wstring file, project;

        // Acquire the application name, time and PID
        activeWindowData data = fetchWindowInfo(target);

        getWindowTitleData(title, titleFormats[data.pname], file, project);
        
        string a = format;
        formatOutput(a, data);

        /* Check if the PID is not equal to the previously acquired PID
            so the output is only printed when the window changes */

        if (data.name != "") cout << a << endl;// << file << " " << project << endl;
        previousData = data;

        Sleep(interval);

    }

    return 0;
}
