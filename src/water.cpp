#include <testobj.h>
#include <images.h>
#include <cmath>
#include <gtx\random.hpp>
#include <gtc\noise.hpp>

Water::Water(glm::vec3 pos,Game* parent) : Object(pos,parent)
{
  textureNumber = textureFromTGA("../assets/water.tga",true);
  clearTriangleData((50+1)*(50+1),50*50*2);
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(50+1);y++)
		for (int x = 0; x<(50+1);x++)
		{
      addPoint(y*(50+1)+x,
               glm::vec3((float)x,
                       0,
			                 (float)y),
                       glm::vec3(0,1,0),
                       1,1,1);
      editTextureCoord(y*(50+1)+x,4.f*x/(50+1),4.f*y/(50+1));
		}
	
  // Populate one triangle (for now) per block
	for (int y = 0; y<50;y++)
		for (int x = 0; x<50;x++)
		{
      addTriangle((y*50+x)*2,
                  y*(50+1) + x,
			            (y+1)*(50+1) + x,
			            y*(50+1) + (x+1));
      addTriangle((y*50+x)*2+1,
                  y*(50+1) + x+1,
			            (y+1)*(50+1) + x,
			            (y+1)*(50+1) + (x+1));
		}
  pushTriangleData();
  objectData.shinyness = 0.05;
  objectData.objectType = OT_WATER;
  updateObjectBO();
}
