#include <stdio.h>

#include <heightmap.h>
#include <noise.h>

FILE* fp;

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
  // Load the file (for fast accessing
  fp = fopen("../assets/smalldata.dat","rb");
  if (!fp)
    fprintf(stderr,"ERROR: HEIGHTMAP DATA NOT FOUND!\n");
}

float getHeightmapData(int x, int y)
{
  if (fp==NULL)
    return 0.f;
  fseek(fp,(x+y*1000)*4,SEEK_SET);
  char raw[4];
  fread(raw,4,1,fp);
  return *((float*)raw)/3-350;
}

