#include <stdio.h>

#include <heightmap.h>
#include <noise.h>

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
}

float getHeightmapData(int x, int y)
{
  FILE* fp = fopen("../smalldata.dat","rb");
  if (not fp)
  {
    fprintf(stderr,"ERROR: HEIGHTMAP DATA NOT FOUND!\n");
    return 0.f;
  }
  fseek(fp,(x+y*1000)*4,SEEK_SET);
  char raw[4];
  fread(raw,4,1,fp);
  fclose(fp);
  return *((float*)raw)/3-350;
}

