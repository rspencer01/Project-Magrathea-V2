#include <gl\glut.h>
#include <time.h>
#include <stdio.h>

#include <fpsCounter.h>

float fps = 0.0;
int currentTime;
int previousTime;
int frameCount;
clock_t lastPrint;

void logFrame()
{
  frameCount++;
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  int timeInterval = currentTime - previousTime;
  if(timeInterval > 1000)
  {
    fps = frameCount / (timeInterval / 1000.0f);
    previousTime = currentTime;
    frameCount = 0;
    printf("Frame rate: %f\n",fps);
  }
}