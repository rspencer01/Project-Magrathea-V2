#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

#ifdef _WIN32
#include <Windows.h>
#endif

class Logger
{
  private:
    FILE* out;
    void beginLog();
#ifdef _WIN32
    HANDLE hConsole;
    WORD colourAttrib;
#endif
  public:
    Logger(FILE*,int);
    void log(const char*,...);
};

#ifdef _WIN32
#define LOG_COLOUR_RED FOREGROUND_RED
#define LOG_COLOUR_YELLOW FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define LOG_COLOUR_GREEN FOREGROUND_GREEN
#endif

extern Logger loge;
extern Logger logw;
extern Logger logi;

#endif