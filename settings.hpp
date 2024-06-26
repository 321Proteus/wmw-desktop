#pragma once

#include <string>
#include <map>
#include <windows.h>

using namespace std;

namespace {

    // Measurement timer frequency (in miliseconds)
    unsigned int interval = 1000;


    // Translations
    string windowStartup = "WMW v1.1 Started\n";


    /* A structure for the fetched windows' data.
        Consists of the window name, process name, PID and the calculated window time. */
    struct activeWindowData {
        int pid;
        string name;
        string time;
        string pname;
        wstring file;
        wstring project;
    };

    string format = "%name %time";


    // A function to format the active window data to an array that could be used by the JS code
    string processInfo(activeWindowData data);


    /* This is the list of all the code editors that should be registered by WMW.
    The app recognizes the programs by their executables' names - you can find them in the task manager.
    I added some examples so the apps I use for coding most frequently.
    Unlisted or misspelled applications will not be recognized! */
    map <string, string> codeEditors = {
        {"idea64.exe", "IntelliJ IDEA Community Edition"},
        {"Code.exe", "Visual Studio Code"},
        {"codeblocks.exe", "CodeBlocks"},
        {"devenv.exe", "Visual Studio 2019"} // This one has a weird name

    };

    /* This is the list of applications' window title formats.
    Regex definitions are allowed. %file and %project are replaced by (.*?) */
    map <string, wstring> titleFormats = {
        {"idea64.exe", L"%project \u2013 %file"}, // this one doesn't work for some reason
        {"Code.exe", L"%file - %project - Visual Studio Code"},
        {"codeblocks.exe", L"%file \\[%project\\] - Code::Blocks 20.03"},
        {"devenv.exe", L"%project - Microsoft Visual Studio"}
    };
}
