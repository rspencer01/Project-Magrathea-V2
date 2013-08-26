#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <tree.h>

Tree::Tree(Vector3 pos,Game* g) : Object(pos,g)
{
  printf("New tree at %f %f %f\n",pos.x,pos.y,pos.z);
  initialiseTriangles();
}

void Tree::initialiseTriangles()
{
	// Begin the operation of setting up triangles
	clearTriangleData();
	
	// Add the trunk.  10 points in a circle, and one on top
	for (int y = 0; y<10;y++)
	{
		addPoint(Vector3(0.5f*(float)sin(y/5.f*3.1415),
						 0.f,
						 0.5f*(float)cos(y/5.f*3.1415)));
	}
	addPoint(Vector3(0.f,10.f,0.f));

	// Add 4 leaf things
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
	
	// Add in all the triangles
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
			addTriangle(11*i + y,11*i + (y+1)%10,11*i + 10);

	// And save
	pushTriangleData();
}
