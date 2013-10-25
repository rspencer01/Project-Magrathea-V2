#include <stdio.h>
#include <math.h>
#include <cloud.h>

/// Initialises the cloud at the position, and constructs it
Cloud::Cloud(Vector3 pos,Game* g) : Object(pos,g)
{
  initialiseTriangles();
  // And set the texture as ours
  textureNumber = textureFromTGA("../assets/testTexture.tga",true);
  billboard = true;
}

void Cloud::initialiseTriangles()
{
  clearTriangleData(4,2);
  addPoint(0,Vector3(0,0,0),Vector3(1,0,0),1,1,1);
  editTextureCoord(0,0,0);
  addPoint(1,Vector3(0,10,0),Vector3(1,0,0),1,1,1);
  editTextureCoord(1,1,0);
  addPoint(2,Vector3(0,10,10),Vector3(1,0,0),1,1,1);
  editTextureCoord(2,1,1);
  addPoint(3,Vector3(0,0,10),Vector3(1,0,0),1,1,1);
  editTextureCoord(3,0,1);
  addTriangle(0,0,1,3);
  addTriangle(1,1,2,3);
  pushTriangleData();
}