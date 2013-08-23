#include <stdio.h>

#include <heightmap.h>
#include <noise.h>

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
}

float getHeightmapData(int x, int y)
{
  FILE* fp = fopen("../../smallData.dat","rb");
  fseek(fp,(x+y*1000)*4,SEEK_SET);
  char raw[4];
  fread(raw,4,1,fp);
  fclose(fp);
  return *((float*)raw)/3-350;
}

