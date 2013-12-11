#include <stdio.h>
#include <math.h>
#include <smallFern.h>

GLuint smallFernTextureNumber = 0;
const char* smallFernTextureName = "../assets/smallFern.tga";

/// Initialises the tree at the position, and constructs it
SmallFern::SmallFern(Vector3 pos,Game* g) : Object(pos,g)
{
  normal = *(g->getTerrainBit((int)pos.x,(int)pos.y).normal);
  initialiseTriangles();
  freeze();
  // If we have yet to load the texture, do so
  if (smallFernTextureNumber == 0)
	  smallFernTextureNumber = textureFromTGA(smallFernTextureName,true);
  // And set the texture as ours
  textureNumber = smallFernTextureNumber;
  
}

void SmallFern::initialiseTriangles()
{
	// Begin the operation of setting up triangles
	clearTriangleData(420,300);
  numberOfPoints = 0;
  numberOfTriangles = 0;

  int seed = (int)position.x;
  Vector3 pos = Vector3();
  // Three leaves equally spaced round the circle
  for (int i = 0;i<7;i++)
  {
    //Multiple increments in one line leads to undefined behaviour - Warning as Error GCC 4.8.1
    int s1 = seed++;
    int s2 = seed++;
    int s3 = seed++;
    Vector3 dir = Vector3(random(s1)*2-1,
                         0.4f+0.2f*random(s2),
                         random(s3)*2-1).normal();
    makeLeaf(pos,dir,2.f,0.05f);
    pos = pos + Vector3(0,0.1f,0);
  }
  //for (int i = 5;i<8;i++)
  //  makeLeaf(Vector3(0,0.3,0),Vector3(random(i+5)*2-1,1.5+0.1*random(i*101+7),random(i*100+1)*2-1)/2.5,3.f,0.12+0.03*random(i*1011+88));

  /*makeLeaf(Vector3(),Vector3(-0.5,1.2,0.866)/2.5,3.f);
  makeLeaf(Vector3(),Vector3(-0.5,1.2,-0.866)/2.5,3.f);
  */
  rotate(randomVector().cross(normal).normal(),normal.normal());

  pushTriangleData();
}

/// Constructs a new leaf at the given position and direction
/// @param pos The position of the bottom
/// @param dir The direction the leaf starts in (but it bends down...)
/// @param width The width of the bottom
void SmallFern::makeLeaf(Vector3 pos, Vector3 dir, float width,float droopyness)
{
  dir.normalise();
  dir = dir*width/5.0;
  Vector3 cross = dir.cross(Vector3(dir.x,0,dir.z)).normal()*width/2;

  cross = cross*0.5;


  addPoint(numberOfPoints,pos+cross,Vector3(0,1,0),0.7f,0.8f,0.2f);
  editTextureCoord(numberOfPoints,0,0);
  numberOfPoints++;
  addPoint(numberOfPoints,pos-cross,Vector3(0,1,0),0.7f,0.8f,0.2f);
  editTextureCoord(numberOfPoints,1,0);
  numberOfPoints++;
  for (int i = 0;i<5;i++)
  {
    // This is not completely accurate...
    Vector3 norm = pos + cross;
    dir = dir - Vector3(0,droopyness,0);
    pos = pos+dir;
    norm = (pos+cross - norm).cross(pos-cross - norm)*-1;
    norm.normalise();
    
    addPoint(numberOfPoints,pos+cross,
      norm,0.7f,0.8f,0.2f);
    editTextureCoord(numberOfPoints,0,((i+1)/5.f));
    numberOfPoints++;
    addPoint(numberOfPoints,pos-cross,
      norm,0.7f,0.8f,0.2f);
    editTextureCoord(numberOfPoints,1,((i+1)/5.f));
    numberOfPoints++;
    addTriangle(numberOfTriangles,numberOfPoints-4,numberOfPoints-3,numberOfPoints-2);
    numberOfTriangles++;
    addTriangle(numberOfTriangles,numberOfPoints-3,numberOfPoints-2,numberOfPoints-1);
    numberOfTriangles++;
  }

}
