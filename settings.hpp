#pragma once

#include <string>
#include <map>
#include <windows.h>

using namespace std;

namespace {

    // Measurement timer frequency (in miliseconds)
    unsigned int interval = 1000;


    // Translations
    string windowStartup = "WMW v1.0 Started\n";


    /* A structure for the fetched windows' data.
        Consists of the window name, PID and the calculated window time. */
    struct activeWindowData {
        int pid;
        string name;
        string time;
    };

    string format = "%name (%pid) - %time";


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
}
