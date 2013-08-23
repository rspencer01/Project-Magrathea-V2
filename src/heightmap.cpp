#include <stdio.h>

#include <heightmap.h>

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
}

float getHeightmapData(int x, int y)
{
  if (x>10)
    return x-10;
  return 0;
}

