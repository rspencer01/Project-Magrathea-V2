#include <stdio.h>
#include <math.h>
#include <magrathea.h>

#include <dynotree.h>
#include <images.h>

// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint dtreeTextureNumber = (GLuint)-1;
// Where is the texture actually stored?
const char* dtextureName = "../assets/BasicTreeTrans1.bmp";

/// Construct a dynoTree at the given location
DynoTree::DynoTree(Vector3 pos,Game* g) : Object(pos,g)
{
  // Actually construct the triangles
  initialiseTriangles();
  // If we have yet to load the texture, do it
  if (dtreeTextureNumber == (GLuint)-1)
	  dtreeTextureNumber = textureFromBMP(dtextureName);
  // And set it as this object's texture
  textureNumber = dtreeTextureNumber;
}

/// Construct the triangles
void DynoTree::initialiseTriangles()
{
	// Begin the operation of setting up triangles
  // Reserve this many (experimentation showed these as good values
	clearTriangleData(3000,2000);
  // Now set these to 0 so that we don't pass too many to th object class.
  // These values will be incrimented by the makeBranch and makeLeaves methods
  numberOfPoints = 0;
  numberOfTriangles = 0;
  // Construct the trunk, 1m below the ground, going up.
  makeBranch(Vector3(0,-1,0),Vector3(0,1,0),3,1,-1,false);
	// And save
	pushTriangleData();
}

void DynoTree::makeBranch(Vector3 pos, Vector3 dir, float len, float width, int lastRingIndex,bool swapTex)
{
  // Add the trunk.  10 points in a circle, and one on top
	// We do one point twice so that the texture is nice
  Vector3 basisA = dir.cross(Vector3(1,0,1)).normal();
  Vector3 basisB = dir.cross(basisA).normal();
  if (lastRingIndex==-1)
  {
    lastRingIndex = numberOfPoints;
    for (int y = 0; y<11;y++)
    {
 	  	addPoint(numberOfPoints,
                pos+
                basisA*width*sin(3.1415*y/5.f)+
                basisB*width*cos(3.1415*y/5.f),
                Vector3(sin(y/5.f*3.1415),0,cos(y/5.f*3.1415)),
                0.58f	,0.35f,0.09f);
       editTextureCoord(numberOfPoints,y*0.0345,0);
       numberOfPoints++;
 	  }
  }
  int tRIng = numberOfPoints;
 	for (int y = 0; y<11;y++)
	{
		addPoint(numberOfPoints,
             pos+
             basisA*width*sin(3.1415*y/5.f)*0.66+
             basisB*width*cos(3.1415*y/5.f)*0.66+dir*len,
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
    Vector3 newDirection = dir + d/1.8;
    makeBranch(pos+dir*len,newDirection.normal(),len/1.2,width*2.0/5.0,-1,false);
    d = randomVector();
    newDirection = dir + d/2.8;
    makeBranch(pos+dir*len,newDirection.normal(),len/1.2,width*3.0/5.0,tRIng,!swapTex);
  }
  if (width<0.3)
    makeLeaves(pos,dir,len);
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

