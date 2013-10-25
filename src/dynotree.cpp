#include <stdio.h>
#include <math.h>
#include <magrathea.h>

#include <dynotree.h>
#include <images.h>

// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint dtreeTextureNumber = (GLuint)-1;
// Where is the texture actually stored?
const char* dtextureName = "../assets/Tree.tga";

/// Construct a dynoTree at the given location
DynoTree::DynoTree(Vector3 pos,Game* g) : Object(pos,g)
{
  // Actually construct the triangles
  initialiseTriangles();
  // If we have yet to load the texture, do it
  if (dtreeTextureNumber == (GLuint)-1)
	  dtreeTextureNumber = textureFromTGA(dtextureName,false);
  // And set it as this object's texture
  textureNumber = dtreeTextureNumber;

  billboard = true;
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

int DynoTree::makeRing(Vector3 pos, Vector3 basisA, Vector3 basisB, float width,bool swapTex)
{
  // Record the index of the beginning, to return
  int lastRingIndex = numberOfPoints;
  // We will make 11 points
  for (int y = 0; y<11;y++)
  {
    // Calculate the angle
    float theta = 3.1415*2.0*y/10.f;
    // And add this point
 		addPoint(numberOfPoints,
              pos+
              basisA*width*sin(theta)+
              basisB*width*cos(theta),
              basisA*sin(theta)+
              basisB*cos(theta),
              0.58f	,0.35f,0.09f);
    // Add the texture coordinate, inverting if required
    editTextureCoord(numberOfPoints,y*0.0345,swapTex?1:0);
    // Log that we added a point
    numberOfPoints++;
 	}
  // Return the index of the first point
  return lastRingIndex;
}

/// Construct the triangles that make up the branch
void DynoTree::makeTriangles(int beginning,int end)
{
  // Ten rectangles
  for (int y = 0; y<10;y++)
  {
    // Add the two triangles
		addTriangle(numberOfTriangles  ,beginning+y,beginning+(y+1),end+y);
		addTriangle(numberOfTriangles+1,beginning+y+1,end+y,end+y+1);
    numberOfTriangles += 2;
  }
}

void DynoTree::makeBranch(Vector3 pos, Vector3 dir, float len, float width, int lastRingIndex,bool swapTex)
{
  // Construct the two basis vectors for construction of points
  Vector3 basisA = dir.cross(Vector3(1,0,1)).normal();
  Vector3 basisB = dir.cross(basisA).normal();
  // If we need to make a bottom ring, do so
  if (lastRingIndex==-1)
    lastRingIndex = makeRing(pos,basisA,basisB,width,true);
  // Otherwise, and in addition, create the top ring
  int topRingIndex = makeRing(pos+dir*len,basisA,basisB,width*0.66,swapTex);
	// Add in all the triangles
	makeTriangles(lastRingIndex,topRingIndex);
  // If the branch is thick enough, we can branch into two others
  if (width>0.05)
  {
    // Get a random direction
    Vector3 d = randomVector();
    // Add it to this direction
    Vector3 newDirection = dir + d/1.8;
    // Make a sub branch in that direction
    makeBranch(pos+dir*len,newDirection.normal(),len/1.2,width*2.0/5.0,-1,false);
    // Do it again
    d = randomVector();
    newDirection = dir + d/2.8;
    // Continue this branch
    makeBranch(pos+dir*len,newDirection.normal(),len/1.2,width*3.0/5.0,topRingIndex,!swapTex);
  }
  // If we are small enough, we can put leaves here
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

