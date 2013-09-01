#include <time.h>
#include <stdio.h>

#include <fpsCounter.h>

float fps = 0.0;
clock_t last;
clock_t lastPrint;

void logFrame()
{
  clock_t next = clock();
  fps = 1.0/(float(next-last)/CLOCKS_PER_SEC);
  last = next;
  if (next-lastPrint > CLOCKS_PER_SEC)
  {
    lastPrint = next;
    printf("Frame Rate %f\n",fps);
  }
}