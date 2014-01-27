/**
 * @file game.h
 * @author Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * Describes the three loggers (error, warning and info) and their methods
 */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

// Lots of stuff is platform specific.  I have done the windows stuff.  You (yes, you) can, if you want,
// do the linux side of this.
#ifdef _WIN32
#include <Windows.h>
#endif

/// A logging class that prints out info in nice formats
class Logger
{
  private:
    // The file to which we are writing the log
    FILE* out;
    // A method that does the timestamp and colour
    void beginLog();
    // Variables needed for the colour dependance.  These are the Windows ones...
#ifdef _WIN32
    HANDLE hConsole;
    WORD colourAttrib;
#else
    // And these are where the linux ones would go
#endif
  public:
    /// Construct a new logger, writing to the given file, with the given log colour
    Logger(FILE*,int);
    /// Log some text
    void log(const char*,...);
};

// Here we define the colours.  For windows, we use SetConsoleTextAtribute, so these are the numbers wanted
#ifdef _WIN32
#define LOG_COLOUR_RED FOREGROUND_RED
#define LOG_COLOUR_YELLOW FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define LOG_COLOUR_GREEN FOREGROUND_GREEN
#else
// For linux, I am sure there are single characters we can print.  They will be defined here.
#endif

// Our three main loggers
/// The error logger
extern Logger loge;
/// The warning logger
extern Logger logw;
/// The info logger
extern Logger logi;

#endif