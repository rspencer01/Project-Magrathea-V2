#include <iostream>
#include <log.h>
#include <time.h>


Logger loge (stdout,LOG_COLOUR_RED);
Logger logw (stdout,LOG_COLOUR_YELLOW);
Logger logi (stdout,LOG_COLOUR_GREEN);

Logger::Logger(FILE* o,int c)
{
  out = o;
#ifdef _WIN32
  if (o==stderr)
  {
    hConsole = GetStdHandle(STD_ERROR_HANDLE);
    colourAttrib = c;
  }
  else
  {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    colourAttrib = c;
  }
#endif
}

void Logger::beginLog()
{
#ifdef _WIN32
  SetConsoleTextAttribute(hConsole,colourAttrib);
#endif

  char buffer [100];
  time_t rawtime;
  time(&rawtime);
  strftime(buffer,100,"%H:%M:%S",localtime(&rawtime));
  fprintf(out,"[%s] ",buffer);

#ifdef _WIN32
  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
#endif
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