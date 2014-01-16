#include <stdio.h>
#include <magrathea.h>
#include <heightmap.h>
#include <gtc\noise.hpp>

FILE* fp;

void initialiseHeightmap()
{
  printf("Initialising heightmap\n");
  // Load the file (for fast accessing
  fp = fopen("../assets/smalldata.dat","rb");
  if (fp==NULL)
    DIE("Heightmap data not found");
}

float getHeightmapData(int x, int y)
{
  return 50.0*glm::perlin(0.005f*glm::vec2((float)x,(float)y))
     + 5.0*glm::perlin(0.05f*glm::vec2((float)x,(float)y));
  /*if (fp==NULL)
    return 0.f;
  fseek(fp,(x+y*1000)*4,SEEK_SET);
  char raw[4];
  fread(raw,4,1,fp);
  return *((float*)raw)/3-350;*/
}

