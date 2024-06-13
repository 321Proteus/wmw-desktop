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

void formatOutput(wstring& text, activeWindowData data) {

    int idx = 0;

    wstring time_w(data.time.begin(), data.time.end());
    wstring name_w(data.name.begin(), data.name.end());
    wstring pname_w(data.pname.begin(), data.pname.end());
    string pidString = to_string(data.pid);
    wstring pid_w(pidString.begin(), pidString.end());

    while (text.find('%') != string::npos) {

        idx = text.find('%', idx);

        wstring temp = text.substr(idx, 4);

        if      (temp == L"%pid")    text.replace(idx, 4, pid_w);
        else if (temp == L"%nam")    text.replace(idx, 5, name_w);
        else if (temp == L"%tim")    text.replace(idx, 5, time_w);
        else if (temp == L"%pna")    text.replace(idx, 6, pname_w);
        else if (temp == L"%fil")    text.replace(idx, 5, data.file);
        else if (temp == L"%pro")    text.replace(idx, 8, data.project);
        else break;
        
    }


}

bool getWindowTitleData(wstring& title, wstring format, wstring& file, wstring& project) {

    wstring regexString = format;
    
    regexString = regex_replace(regexString, wregex(L"%file"), L"(.*?)");
    regexString = L"^" + regex_replace(regexString, wregex(L"%project"), L"(.*?)") + L"$"; 

    //swcout << regexString << L" ";

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

        data.file = file;
        data.project = project;
        
        wstring a(format.begin(), format.end());
        formatOutput(a, data);

        /* Check if the PID is not equal to the previously acquired PID
            so the output is only printed when the window changes */

        if (data.name != "") wcout << a << endl;// << file << " " << project << endl;
        previousData = data;

        Sleep(interval);

    }

    return 0;
}
