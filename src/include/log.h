#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>

class Logger
{
  private:
    FILE* out;
    void beginLog();
  public:
    Logger(FILE*);
    void log(const char*,...);
};

extern Logger loge;
extern Logger logw;
extern Logger logi;

#endif