#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <tree.h>
#include <images.h>

GLuint treeTextureNumber = (GLuint)-1;
const char* textureNames[3] = {"../../assets/BasicTree1.bmp","../../assets/BasicTree2.bmp","../../assets/BasicTree3.bmp"};

Tree::Tree(Vector3 pos,Game* g) : Object(pos,g)
{
  initialiseTriangles();
  if (treeTextureNumber == (GLuint)-1)
	  treeTextureNumber = textureFromBMP(textureNames[2]);
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
             Vector3(sin(y/5.f*3.1415),0,cos(y/5.f*3.1415)),
             0.58f,0.35f,0.09f);
		editTextureCoord(y,y*0.0345,0);
	}
	addPoint(11,Vector3(0.f,10.f,0.f),Vector3(0,1,0),0.58f,0.35f,0.09f);
	editTextureCoord(11,0.019,1);
	
	// Add 4 leaf things
	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<11;y++)
		{
			addPoint(12+i*12+y,
               Vector3((4-i)*(float)sin(y/5.f*3.1415),
							 (i+3-0.5f)*10.f/7,
							 (4-i)*(float)cos(y/5.f*3.1415)),
               Vector3(sin(y/5.f*3.1415),0.7,cos(y/5.f*3.1415)).normal()
               ,0.25f,0.5f,0.15f);
			editTextureCoord(12+i*12+y,0.77+0.23*sin(y/5.f*3.1415),0.5+0.23*cos(y/5.f*3.1415));
		}
		addPoint(12+i*12+11,Vector3(0.f,(i+3)*10.f/7,0.f),Vector3(0,1,0),0.25f,0.5f,0.15f);
		editTextureCoord(12+i*12+11,0.77,0.5);
	}
	
	// Add in all the triangles
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
			addTriangle(i*10+y,12*i + y,12*i + (y+1),12*i + 11);

	// And save
	pushTriangleData();
}
