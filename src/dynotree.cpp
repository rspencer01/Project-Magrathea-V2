#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <dynotree.h>
#include <images.h>
#include <noise.h>

GLuint dtreeTextureNumber = (GLuint)-1;
const char* dtextureName = "../assets/BasicTree3.bmp";

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
	clearTriangleData(10000,6000);
  // Now set these to 0 so that we don't pass too many
  numberOfPoints = 0;
  numberOfTriangles = 0;
  makeBranch(Vector3(0,-1,0),Vector3(0,1,0),10,1);
	
	// And save
	pushTriangleData();
}

void DynoTree::makeBranch(Vector3 pos, Vector3 dir, float len, float width)
{
  // Add the trunk.  10 points in a circle, and one on top
	// We do one point twice so that the texture is nice
  Vector3 basisA = dir.cross(Vector3(1,0,1)).normal();
  Vector3 basisB = dir.cross(basisA).normal();
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
 	for (int y = 0; y<11;y++)
	{
		addPoint(numberOfPoints,
             pos+
             basisA*width*sin(3.1415*y/5.f)*0.5+
             basisB*width*cos(3.1415*y/5.f)*0.5+dir*len,
             Vector3(sin(y/5.f*3.1415),0,cos(y/5.f*3.1415)),
             0.58f	,0.35f,0.09f);
    editTextureCoord(numberOfPoints,y*0.0345,1);
    numberOfPoints++;
	}
		
	// Add in all the triangles
	for (int y = 0; y<10;y++)
  {
		addTriangle(numberOfTriangles,numberOfPoints-22+y,numberOfPoints-22+(y+1),numberOfPoints-11+y);
    numberOfTriangles++;
		addTriangle(numberOfTriangles,numberOfPoints-22+y+1,numberOfPoints-10+y,numberOfPoints-11+y);
    numberOfTriangles++;
}
  
  if (width>0.1)
  {
    for (int i = 0; i <3 ;i++)
    {
      float p = random((int)(position+pos).x*1000*+i+numberOfTriangles*numberOfPoints);
      float q = random(20+(int)(position+pos).x*1000+i+numberOfPoints)-0.5;
      float r = random(40+(int)(position+pos).x*1000+i+numberOfTriangles)-0.5;
      Vector3 d = dir + basisA*q*3+basisB*r*3;
      makeBranch(pos+dir*len*(0.5+0.4*p),d.normal(),len/1.7,width/2.5);
    }
  }
  
}