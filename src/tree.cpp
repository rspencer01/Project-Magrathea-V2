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
	// This will hold the vertex position data
	float* triangleData = new float[11*3*5];
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<10;y++)
	{
		triangleData[y*3    ] = position.x + 0.5f*(float)sin(y/5.f*3.1415);
		triangleData[y*3 + 1] = position.z;
		triangleData[y*3 + 2] = position.y + 0.5f*(float)cos(y/5.f*3.1415);
	}
	triangleData[10*3  ] = position.x;
	triangleData[10*3+1] = position.z + 10.f;
	triangleData[10*3+2] = position.y;

	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<10;y++)
		{
			triangleData[((i+1)*11+y)*3    ] = position.x + (4-i)*(float)sin(y/5.f*3.1415);
			triangleData[((i+1)*11+y)*3 + 1] = position.z + (i+3-0.5f)*10.f/7;
			triangleData[((i+1)*11+y)*3 + 2] = position.y + (4-i)*(float)cos(y/5.f*3.1415);
		}
		triangleData[((i+1)*11+10)*3] = position.x;
		triangleData[((i+1)*11+10)*3+1] = position.z + (i+3)*10.f/7;
		triangleData[((i+1)*11+10)*3+2] = position.y;
	}

	// Now make a buffer...
	glGenBuffersARB(1,&vertexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, 11*3*5*sizeof(float), triangleData,GL_STATIC_DRAW);
	// We are done with this data, so free it, please.
	// TODO Why does this cause a crash???
	//delete[] triangleData;

	// As above, each of the REGION_SIZE*REGION_SIZE gets 3 vertices
	int* indexData = new int[50*3];
	// Populate one triangle (for now) per block
	for (int i = 0;i<5;i++)
		for (int y = 0; y<10;y++)
		{
			indexData[(i*10 + y)*3    ] = 11*i + y;
			indexData[(i*10 + y)*3 + 1] = 11*i + (y+1)%10;
			indexData[(i*10 + y)*3 + 2] = 11*i + 10;
		}

	// Make another buffer...
	glGenBuffersARB(1,&indexVBO);
	// an element array buffer (which we mount),
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	// ... and put the data in.
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, 50*3*sizeof(int), indexData,GL_STATIC_DRAW);
	// Then again, free this up
	delete[] indexData;	

	// Now we have initialised these things, so they can be released if required
	buffersInitialised = true;
	numberOfTriangles = 50;
}
