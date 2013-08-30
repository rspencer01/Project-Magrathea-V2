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
	clearTriangleData(3000,2000);
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
  int lastRingIndex  = branch.basePointsIndex;
  
  // What is the centre of the start of the branch
  Vector3 startPoint = *(branch.pos);
  // What is the centre of the end of the branch
  Vector3 endPoint = startPoint + *(branch.direction)*branch.len;

  // Get the two basis: two vector perpendicular to the direction of the branch
  Vector3 basisA = branch.direction->cross(Vector3(1,0,1)).normal();
  Vector3 basisB = branch.direction->cross(basisA).normal();
  // In the case that we need ot start an entirely new branch (no starting ring already)
  if (branch.basePointsIndex == -1)
  {
    // State that the last ring is this one
    lastRingIndex = numberOfPoints;
    branch.basePointsIndex = numberOfPoints;
    // Construct 11 points (for the 10 triangles)
    for (int y = 0; y<11;y++)
    {
      // Equally spaced around the trunk
      float theta = 3.1415 * 2.0 * y / 10.0;
      // Calculate the offset from the trunk centre
      Vector3 displacement = (basisA*sin(theta)+basisB*cos(theta)) * branch.width/0.6;
      // Add this point
 	  	addPoint(numberOfPoints,
               startPoint+displacement,
               displacement,
               0.58f	,0.35f,0.09f);
      // The texture coordinate
      editTextureCoord(numberOfPoints,y*0.0345,0);
      // We have added a point.  Reflect this
      numberOfPoints++;
 	  }
    branch.reverseTexture = false;
  }
  // Record the starting index of the top ring
  int topRingIndex = numberOfPoints;
  // Now add a ring of points at the top, in basically the same way
 	for (int y = 0; y<11;y++)
	{
    // Calculate the angle
    float theta = 3.1415 * 2.0 * y / 10.0;
    // Calculate the offset from the trunk centre
    Vector3 displacement = (basisA*sin(theta)+basisB*cos(theta)) * branch.width;
		addPoint(numberOfPoints,
             endPoint+displacement,
             displacement,
             0.58f	,0.35f,0.09f);
    // If we need to revese the texture, do so
    if (branch.reverseTexture)
      editTextureCoord(numberOfPoints,y*0.0345,0);
    else
      editTextureCoord(numberOfPoints,y*0.0345,1);
    // Record this point
    numberOfPoints++;
	}
		
	// Add in all the triangles for this branch. There are 20 as this is a cylinder
  for (int y = 0; y<10;y++)
  {
		addTriangle(numberOfTriangles,lastRingIndex+y,lastRingIndex+(y+1),numberOfPoints-11+y);
    numberOfTriangles++;
		addTriangle(numberOfTriangles,lastRingIndex+y+1,numberOfPoints-10+y,numberOfPoints-11+y);
    numberOfTriangles++;
  }

  // If the branch is thick enough, we can split into two
  if (branch.width>0.05)
  {
    // Get a random vector...
    Vector3 d = randomVector();
    // And add it (scaled) to the current direction.  Get the new direction in normal form
    Vector3 newDirection = *(branch.direction) + d/1.8;
    newDirection.normalise();
    // Now reserve some space for the new branch data
    branchStruct subBranch;
    // Both branches start from the same point: the top of this branch
    subBranch.pos = new Vector3(endPoint);
    subBranch.direction = new Vector3(newDirection);
    // Shorten the branch, and make it smaller
    subBranch.len = branch.len / 1.2;
    subBranch.width = branch.width * 0.4;
    // Swap the texture output
    subBranch.reverseTexture = !branch.reverseTexture;
    // Tell this branch to start on this ring
    subBranch.basePointsIndex = -1;
    makeBranch(subBranch);
    
    d = randomVector();
    newDirection = *(branch.direction) + d/2.8;
    subBranch.pos = new Vector3(endPoint);
    subBranch.direction = new Vector3(newDirection.normal());
    subBranch.width = branch.width * 0.6;
    subBranch.basePointsIndex = topRingIndex;


    makeBranch(subBranch);
  }
  
  // If the width is less than a certain limit, populate this branch with leaves
  if (branch.width<0.3)
    makeLeaves(startPoint,*(branch.direction),branch.len);
  // Clean up the dyncamic variables passed to this function
  delete branch.pos;
  delete branch.direction;
}

void DynoTree::makeLeaves(Vector3 pos, Vector3 dir, float len)
{
  for (int i = 1;i<6;i++)
  {
    Vector3 leafDir = dir.normal() * 0.5 + randomVector()*0.5;
    leafDir.y /= 2;
    leafDir.normalise();
    Vector3 leafCross = leafDir.cross(randomVector()).normal()*0.5;
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

