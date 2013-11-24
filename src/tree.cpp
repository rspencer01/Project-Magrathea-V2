#include <stdio.h>
#include <math.h>
#include <tree.h>

GLuint treeTextureNumber = (GLuint)-1;
const char* textureName = "../assets/BasicTree3.bmp";

/// Initialises the tree at the position, and constructs it
Tree::Tree(Vector3 pos,Game* g) : Object(pos,g)
{
  initialiseTriangles();
  // If we have yet to load the texture, do so
  if (treeTextureNumber == (GLuint)-1)
	  treeTextureNumber = textureFromBMP(textureName);
  // And set the texture as ours
  textureNumber = treeTextureNumber;
}

void Tree::initialiseTriangles()
{
	// Begin the operation of setting up triangles
	clearTriangleData(12*5,10*5);
	
	// Add the trunk.  10 points in a circle, and one on top
	// We do one point twice so that the texture is nice
	for (int y = 0; y<11;y++)
	{
		addPoint(y,
             Vector3(0.5f*(float)sin(y/5.f*3.1415),
						 -1.f,
						 0.5f*(float)cos(y/5.f*3.1415)),
             Vector3((float)sin(y/5.f*3.1415),0,(float)cos(y/5.f*3.1415)),
             0.58f,0.35f,0.09f);
		editTextureCoord(y,y*0.0345f,0);
	}
	addPoint(11,Vector3(0.f,10.f,0.f),Vector3(0,1,0),0.58f,0.35f,0.09f);
	editTextureCoord(11,0.019f,1.f);
	
	// Add 4 leaf things
	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<11;y++)
		{
			addPoint(12+i*12+y,
               Vector3((4-i)*(float)sin(y/5.f*3.1415),
							 (i+3-0.5f)*10.f/7,
							 (4-i)*(float)cos(y/5.f*3.1415)),
               Vector3((float)sin(y/5.f*3.1415),0.7f,(float)cos(y/5.f*3.1415)).normal()
               ,0.25f,0.5f,0.15f);
			editTextureCoord(12+i*12+y,(float)(0.77+0.23*sin(y/5.f*3.1415)),(float)(0.5+0.23*cos(y/5.f*3.1415)));
		}
		addPoint(12+i*12+11,Vector3(0.f,(i+3)*10.f/7,0.f),Vector3(0,1,0),0.25f,0.5f,0.15f);
		editTextureCoord(12+i*12+11,0.77f,0.5f);
	}
	
	// Add in all the triangles
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
			addTriangle(i*10+y,12*i + y,12*i + (y+1),12*i + 11);

	// And save
	pushTriangleData();
}
