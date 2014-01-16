#include <testobj.h>
#include <images.h>
#include <cmath>
#include <gtx\random.hpp>
#include <gtc\noise.hpp>

Water::Water(glm::vec3 pos,Game* parent) : Object(pos,parent)
{
  int waterSize = 600;
  int detail = 1;
  textureNumber = textureFromTGA("../assets/water.tga",true);
  clearTriangleData((waterSize+1)*(waterSize+1),waterSize*waterSize*2);
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(waterSize+1);y++)
		for (int x = 0; x<(waterSize+1);x++)
		{
      addPoint(y*(waterSize+1)+x,
               glm::vec3((float)x*detail,
                       0,
			                 (float)y*detail),
                       glm::vec3(0,1,0),
                       1,1,1);
      editTextureCoord(y*(waterSize+1)+x,4.f*x/(waterSize+1),4.f*y/(waterSize+1));
		}
	
  // Populate one triangle (for now) per block
	for (int y = 0; y<waterSize;y++)
		for (int x = 0; x<waterSize;x++)
		{
      addTriangle((y*waterSize+x)*2,
                  y*(waterSize+1) + x,
			            (y+1)*(waterSize+1) + x,
			            y*(waterSize+1) + (x+1));
      addTriangle((y*waterSize+x)*2+1,
                  y*(waterSize+1) + x+1,
			            (y+1)*(waterSize+1) + x,
			            (y+1)*(waterSize+1) + (x+1));
		}
  pushTriangleData();
  objectData.shinyness = 0.05;
  objectData.objectType = OT_WATER;
  updateObjectBO();
}
