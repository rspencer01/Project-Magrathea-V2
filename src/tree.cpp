#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <tree.h>

Tree::Tree(int x, int y,int z,Game* g) : Object(Vector3((float)x,(float)y,(float)z),g)
{
	printf("New tree at %d %d\n",x,y);
    initialiseTriangles();
}

void Tree::initialiseTriangles()
{
	clearTriangleData();
	// This will hold the vertex position data
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<10;y++)
	{
		addPoint(Vector3(0.5f*(float)sin(y/5.f*3.1415),
						 0.f,
						 0.5f*(float)cos(y/5.f*3.1415)));
	}
	addPoint(Vector3(0.f,10.f,0.f));

	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<10;y++)
		{
			addPoint(Vector3((4-i)*(float)sin(y/5.f*3.1415),
							 (i+3-0.5f)*10.f/7,
							 (4-i)*(float)cos(y/5.f*3.1415)));
		}
		addPoint(Vector3(0.f,(i+3)*10.f/7,0.f));
	}


	// Populate one triangle (for now) per block
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
			addTriangle(11*i + y,11*i + (y+1)%10,11*i + 10);

	pushTriangleData();
}
