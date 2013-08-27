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
	clearTriangleData(55,50);
	
	// Add the trunk.  10 points in a circle, and one on top
	for (int y = 0; y<10;y++)
	{
		addPoint(y,
             Vector3(0.5f*(float)sin(y/5.f*3.1415),
						 0.f,
						 0.5f*(float)cos(y/5.f*3.1415)),0.58f,0.35f,0.09f);
	}
	addPoint(10,Vector3(0.f,10.f,0.f),0.58f,0.35f,0.09f);

	// Add 4 leaf things
	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<10;y++)
		{
			addPoint(11+i*11+y,
               Vector3((4-i)*(float)sin(y/5.f*3.1415),
							 (i+3-0.5f)*10.f/7,
							 (4-i)*(float)cos(y/5.f*3.1415)),0,0.4f,0);
		}
		addPoint(11+i*11+10,Vector3(0.f,(i+3)*10.f/7,0.f),0,0.4f,0);
	}
	
	// Add in all the triangles
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
			addTriangle(i*10+y,11*i + y,11*i + (y+1)%10,11*i + 10);

	// And save
	pushTriangleData();
}
