#include <magrathea.h>
#include <heightmap.h>
#include <gtx\noise.hpp>

/// Nothing is done here.  In the future this may include some preprocessing
void initialiseHeightmap()
{
}

/// Returns a nice multi octave perlin noise
float getHeightmapData(int x, int y)
{
  return 0;
  return 50.0*glm::perlin(0.005f*glm::vec2((float)x,(float)y))
     + 5.0*glm::perlin(0.05f*glm::vec2((float)x,(float)y));
}

