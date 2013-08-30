#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <dynotree.h>
#include <images.h>
#include <noise.h>

GLuint dtreeTextureNumber = (GLuint)-1;
const char* dtextureName = "../assets/BasicTreeTrans1.bmp";

DynoTree::DynoTree(Vector3 pos,Game* g) : Object(pos,g)
{
  initialiseTriangles();
  if (dtreeTextureNumber == (GLuint)-1)
	  dtreeTextureNumber = textureFromBMP(dtextureName);
  textureNumber = dtreeTextureNumber;
}

void DynoTree::initialiseTriangles()
{
	// Begin the operation of setting up triangles
  // Reserve far too many than we actually need
	clearTriangleData(5000,5000);
  // Now set these to 0 so that we don't pass too many
  numberOfPoints = 0;
  numberOfTriangles = 0;
  // Make a branch
  branchStruct trunk;
  trunk.pos = new Vector3(0,-1,0);
  trunk.direction = new Vector3(0,1,0);
  trunk.len = 3;
  trunk.width = 1;
  trunk.reverseTexture = false;
  trunk.basePointsIndex = -1;
  makeBranch(trunk);
	
	// And save
	pushTriangleData();
}

void DynoTree::makeBranch(branchStruct branch)
{
  Vector3 pos = *(branch.pos);
  Vector3 dir = *(branch.direction);
  float len = branch.len;
  float width = branch.width;
  int lastRingIndex  = branch.basePointsIndex;
  bool swapTex = branch.reverseTexture;

  Vector3 startPoint = *(branch.pos);
  Vector3 endPoint = startPoint + *(branch.direction)*branch.len;

  // Add the trunk.  10 points in a circle, and one on top
	// We do one point twice so that the texture is nice
  // Get the two basis: two vector perpendicular to the direction of the branch
  Vector3 basisA = branch.direction->cross(Vector3(1,0,1)).normal();
  Vector3 basisB = branch.direction->cross(basisA).normal();
  if (branch.basePointsIndex == -1)
  {
    lastRingIndex = numberOfPoints;
    branch.basePointsIndex = numberOfPoints;
    for (int y = 0; y<11;y++)
    {
      float theta = 3.1415 * 2.0 * y / 10.0;
      Vector3 displacement = (basisA*sin(theta)+basisB*cos(theta)) * branch.width;
 	  	addPoint(numberOfPoints,
                pos+displacement,
                displacement,
                0.58f	,0.35f,0.09f);
       editTextureCoord(numberOfPoints,y*0.0345,0);
       numberOfPoints++;
 	  }
  }
  int tRIng = numberOfPoints;
 	for (int y = 0; y<11;y++)
	{
		addPoint(numberOfPoints,
             endPoint+
             basisA*width*sin(3.1415*y/5.f)*0.66+
             basisB*width*cos(3.1415*y/5.f)*0.66,
             Vector3(sin(y/5.f*3.1415),0,cos(y/5.f*3.1415)),
             0.58f	,0.35f,0.09f);
    if (swapTex)
      editTextureCoord(numberOfPoints,y*0.0345,0);
    else
      editTextureCoord(numberOfPoints,y*0.0345,1);

    numberOfPoints++;
	}
		
	// Add in all the triangles
	
  for (int y = 0; y<10;y++)
  {
		addTriangle(numberOfTriangles,lastRingIndex+y,lastRingIndex+(y+1),numberOfPoints-11+y);
    numberOfTriangles++;
		addTriangle(numberOfTriangles,lastRingIndex+y+1,numberOfPoints-10+y,numberOfPoints-11+y);
    numberOfTriangles++;
  }
  
  if (width>0.05)
  {
    Vector3 d = randomVector();
    Vector3 newDirection = *(branch.direction) + d/1.8;
    branchStruct subBranch;
    subBranch.pos = new Vector3(pos+dir*len);
    subBranch.direction = new Vector3(newDirection.normal());
    subBranch.len = len / 1.2;
    subBranch.width = width * 0.4;
    subBranch.reverseTexture = !swapTex;
    subBranch.basePointsIndex = tRIng;
    makeBranch(subBranch);
    
    d = randomVector();
    newDirection = dir + d/2.8;
    subBranch.pos = new Vector3(pos+dir*len);
    subBranch.direction = new Vector3(newDirection.normal());
    subBranch.len = len / 1.2;
    subBranch.width = width * 0.6;
    subBranch.reverseTexture = !swapTex;
    subBranch.basePointsIndex = tRIng;


    makeBranch(subBranch);//pos+dir*len,newDirection.normal(),len/1.2,width*3.0/5.0,tRIng,!swapTex);
  }
  if (width<0.3)
    makeLeaves(pos,dir,len);
  delete branch.pos;
  delete branch.direction;
}

void DynoTree::makeLeaves(Vector3 pos, Vector3 dir, float len)
{
  for (int i = 1;i<6;i++)
  {
    Vector3 leafDir = dir.normal() * 0.5 + randomVector()*0.5;
    Vector3 leafCross = leafDir.cross(Vector3(random(i+pos.x*1000),0,random(i+pos.y*1000))).normal()*0.5;
    Vector3 leafPos = pos + dir*len/6.0*i + leafDir*0.3;
    leafDir = leafDir*2;
    leafCross = leafCross*2;

  	addPoint(numberOfPoints,
             leafPos,
             Vector3(0,1,0),
             0.f,0.7f,0.0f);
    editTextureCoord(numberOfPoints,0.38,1);
    numberOfPoints++;
   	addPoint(numberOfPoints,
             leafPos+leafDir/2.0+leafCross,
             Vector3(0,1,0),
             0.f	,0.7f,0.f);
    editTextureCoord(numberOfPoints,0.63,1);
    numberOfPoints++;
   	addPoint(numberOfPoints,
             leafPos+leafDir,
             Vector3(0,1,0),
             0.f,0.7f,0.f);
    editTextureCoord(numberOfPoints,0.63,0.75);
    numberOfPoints++;
    addTriangle(numberOfTriangles,numberOfPoints-2,numberOfPoints-1,numberOfPoints-3);
    numberOfTriangles++;

   	addPoint(numberOfPoints,
             leafPos+leafDir/2.0-leafCross,
             Vector3(0,1,0),
             0.f	,0.7f,0.f);
    editTextureCoord(numberOfPoints,0.38,0.75);
    numberOfPoints++;
    addTriangle(numberOfTriangles,numberOfPoints-2,numberOfPoints-1,numberOfPoints-4);
    numberOfTriangles++;
  
  }
}

