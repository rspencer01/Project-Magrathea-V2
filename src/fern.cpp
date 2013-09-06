#include <stdio.h>
#include <math.h>
#include <fern.h>

GLuint fernTextureNumber = (GLuint)-1;
const char* fernTextureName = "../assets/fern.bmp";

/// Initialises the tree at the position, and constructs it
Fern::Fern(Vector3 pos,Game* g) : Object(pos,g)
{
  initialiseTriangles();
  // If we have yet to load the texture, do so
  if (fernTextureNumber == (GLuint)-1)
	  fernTextureNumber = textureFromBMP(fernTextureName);
  // And set the texture as ours
  textureNumber = fernTextureNumber;
}

void Fern::initialiseTriangles()
{
	// Begin the operation of setting up triangles
	clearTriangleData(60,30);
  numberOfPoints = 0;
  numberOfTriangles = 0;
  makeLeaf(Vector3(),Vector3(1,1.2,0)/2.5,1.f);
  makeLeaf(Vector3(),Vector3(-0.5,1.2,0.866)/2.5,1.f);
  makeLeaf(Vector3(),Vector3(-0.5,1.2,-0.866)/2.5,1.f);
  pushTriangleData();
}

void Fern::makeLeaf(Vector3 pos, Vector3 dir, float width)
{
  int t = numberOfPoints;
  Vector3 cross = dir.cross(Vector3(dir.x,0,dir.z)).normal()*width/2;
  Vector3 diff = (cross*-1)/5+Vector3(0.01,0,0);
  addPoint(numberOfPoints,pos+cross,Vector3(0,1,0),0.7f,0.7f,0.7f);
  editTextureCoord(numberOfPoints,0,0);
  numberOfPoints++;
  addPoint(numberOfPoints,pos-cross,Vector3(0,1,0),0.7f,0.7f,0.7f);
  editTextureCoord(numberOfPoints,1,0);
  numberOfPoints++;
  for (int i = 0;i<5;i++)
  {
    // This is not completely accurate...
    Vector3 norm = pos + cross;
    dir = dir - Vector3(0,0.07,0);
    cross = cross+diff;
    pos = pos+dir;
    norm = (pos+cross - norm).cross(pos-cross - norm)*-1;
    norm.normalise();
    
    addPoint(numberOfPoints,pos+cross,
      norm,0.7f,0.7f,0.7f);
    editTextureCoord(numberOfPoints,0.5*((i+1)/5.f),((i+1)/5.f));
    numberOfPoints++;
    addPoint(numberOfPoints,pos-cross,
      norm,0.7f,0.7f,0.7f);
    editTextureCoord(numberOfPoints,1.f-0.5*((i+1)/5.f),((i+1)/5.f));
    numberOfPoints++;
    addTriangle(numberOfTriangles,numberOfPoints-4,numberOfPoints-3,numberOfPoints-2);
    numberOfTriangles++;
    addTriangle(numberOfTriangles,numberOfPoints-3,numberOfPoints-2,numberOfPoints-1);
    numberOfTriangles++;
  }

}
