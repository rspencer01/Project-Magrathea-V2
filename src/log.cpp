#include <iostream>
#include <log.h>
#include <time.h>

//The actuall definition of these three.
Logger loge (stdout,LOG_COLOUR_RED);
Logger logw (stdout,LOG_COLOUR_YELLOW);
Logger logi (stdout,LOG_COLOUR_GREEN);

/// Constructs the logger
/// @param The file to write to
/// @param The colour to write the timestamp
Logger::Logger(FILE* o,int c)
{
  // Store the file pointer
  out = o;
  // Store the required variables for the colours
#ifdef _WIN32
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  colourAttrib = c;
#endif
}

void Logger::beginLog()
{
  //Set the colour
#ifdef _WIN32
  SetConsoleTextAttribute(hConsole,colourAttrib);
#endif

  // Write the time
  char buffer [100];
  time_t rawtime;
  time(&rawtime);
  strftime(buffer,100,"%H:%M:%S",localtime(&rawtime));
  fprintf(out,"[%s] ",buffer);

  // Reset the colour
#ifdef _WIN32
  SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
#endif
}

void Logger::log(const char* format, ...)
{
  // Write the time stamp ...
  beginLog();

  // ... the actual message ...
  va_list args;
  va_start (args, format);
  vfprintf(out, format, args);
  va_end(args);

  // ... and a newline
  fprintf(out,"\n");
}