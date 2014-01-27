#include <iostream>
#include <log.h>
#include <time.h>

Logger loge (stdout);
Logger logw (stdout);
Logger logi (stdout);

Logger::Logger(FILE* o)
{
  out = o;
}

void Logger::beginLog()
{
  char buffer [100];
  time_t rawtime;
  time(&rawtime);
  strftime(buffer,100,"%H:%M:%S",localtime(&rawtime));
  fprintf(out,"[%s] ",buffer);
}

void Logger::log(const char* format, ...)
{
  beginLog();

  va_list args;
  va_start (args, format);
  vfprintf(out, format, args);
  va_end(args);

  fprintf(out,"\n");
}