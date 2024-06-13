# wmw-desktop
What's My Window (WMW) is a simple C++ utility for detecting active application from the OS, designed to display activity in code editors in the Internet.

WMW uses Windows API to get the foreground window and output its name and elapsed time using (by default) the following scheme:
```
MyAppName hh:mm:ss
```

where `MyAppName` is the application name and then comes the time.

# Installation
WMW is currently available to use on Windows (though Mac and Linux releases are also planned). The binary is built by pasting the following line into your terminal:
```
g++ .\main.cpp .\processInfo.cpp -o wmw.exe -lpsapi
```

# Configuration

WMW can be widely personalised to the user's needs by changing the values in `settings.hpp`:

`unsigned int interval` - the interval between two window requests in miliseconds (default: `1000`)

`string format` - the format of the WMW output. 
Available placeholders:
 - `%name` - current application name
 - `%time` - current application time
 - `%pname` - current process name
 - `%pid` - current process ID
 - `%file` - current file name
 - `%project` - current project name

Default: `%name %time`

`string windowStartup` - the text to display on application startup (used for future translation purposes)

`codeEditors` - a list of key/value pairs of the applications' process names and the corresponding window titles\
(Tip: process names can be obtained via the details tab of the Task Manager)

`titleFormats` - a list of key/value pairs of the process names and the corresponding user-defined window title formats, used to detect file and project names.\
(Tip: as formats may contain Unicode characters, detecting them by hand may be difficult. If you're experiencing problems with the title detection, use the debug funtion at lines 112-114 to read the title as integer values letter by letter)

**Remember**: the settings are stored in the WMW binary and you have to rebuild it to apply the changes!

# To Do

 - ~~Add file name/project name detection for the code editors - the window title usually contains them~~
 - Improve the example project by making it refresh automatically every second
 - ~~Add the ability to personalise the output structure in the config, e.g. adding the process name or the PID~~

Feel free to open a pull request if you develop a solution of one of these (new ideas are also welcome)!


# Example 
The repository contains an example project using the WMW interface - a basic functionality of HTTP display of the current window.
To open it, install Node.js and NPM and run `npm install` in the `example` folder to download the Node libraries and then `node main.js` to run the app.
Then open [localhost:5500](http://localhost:5500) in your browser and you should see the WMW output!
