#include <stdio.h>
#include <grass.h>
#include <noise.h>

// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint grassTextureNumber = (GLuint)-1;
// Where is the texture actually stored?
const char* grassName = "../assets/grass.tga";


Grass::Grass(Vector3 pos, Vector3 norm, Game* parent) : Object(pos,parent)
{
  // If we have yet to load the texture, do it
  if (grassTextureNumber == (GLuint)-1)
	  grassTextureNumber = textureFromTGA(grassName,false);
  // And set it as this object's texture
  textureNumber = grassTextureNumber;
  
  // Get a random vector in the xz plane to orient this grass
  Vector3 horis = Vector3(1,0,0).cross(norm);
  horis.normalise();

  // 8 points and 4 triangles
  clearTriangleData(4,2);
  // Construct the on cross
  addPoint(0,horis          ,Vector3(0,1,0),1,1,1);
  editTextureCoord(0,0,0);
  addPoint(1,horis+norm     ,Vector3(0,1,0),1,1,1);
  editTextureCoord(1,0,1);
  addPoint(2,horis*-1       ,Vector3(0,1,0),1,1,1);
  editTextureCoord(2,1,0);
  addPoint(3,horis*-1+norm  ,Vector3(0,1,0),1,1,1);
  editTextureCoord(3,1,1);
  addTriangle(0,0,1,2);
  addTriangle(1,1,2,3);
 
  updateMatrix();
  pushTriangleData();
}
