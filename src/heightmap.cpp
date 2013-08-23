#include <stdio.h>

#include <heightmap.h>
#include <noise.h>

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
}

float getHeightmapData(int x, int y)
{
  return 50*perlinNoise(x/50.0,y/50.0,8,0.5);
}

