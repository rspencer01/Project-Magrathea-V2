#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <tree.h>

Tree::Tree(int x, int y,int z)
{
	printf("New region at %d %d\n",x,y);
	origin_x = x;
	origin_y = y;
	origin_z = z;
    buffersInitialised = false;
	initialiseTriangles();
}

Tree::~Tree()
{
	if (buffersInitialised)
	{
		glDeleteBuffersARB(1,&vertexVBO);
		glDeleteBuffersARB(1,&indexVBO);
	}
}

void Tree::initialiseTriangles()
{
	// This will hold the vertex position data
	float* triangleData = new float[11*3*5];
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<10;y++)
	{
		triangleData[y*3    ] = (float)(origin_x) + 0.5f*(float)sin(y/5.f*3.1415);
		triangleData[y*3 + 1] = origin_z;
		triangleData[y*3 + 2] = (float)(origin_y) + 0.5f*(float)cos(y/5.f*3.1415);
	}
	triangleData[10*3] = (float)origin_x;
	triangleData[10*3+1] = origin_z + 10.f;
	triangleData[10*3+2] = (float)origin_y;

	for (int i = 0; i<4;i++)
	{
		for (int y = 0; y<10;y++)
		{
			triangleData[((i+1)*11+y)*3    ] = (float)(origin_x) + (4-i)*(float)sin(y/5.f*3.1415);
			triangleData[((i+1)*11+y)*3 + 1] = origin_z + (i+3-0.5)*10.f/7;
			triangleData[((i+1)*11+y)*3 + 2] = (float)(origin_y) + (4-i)*(float)cos(y/5.f*3.1415);
		}
		triangleData[((i+1)*11+10)*3] = (float)origin_x;
		triangleData[((i+1)*11+10)*3+1] = origin_z + (i+3)*10.f/7;
		triangleData[((i+1)*11+10)*3+2] = (float)origin_y;
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
}

void Tree::Render()
{
	// We are passing vertices ...
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
	glVertexPointer( 3, GL_FLOAT, 0, 0);
	// ... and indexes
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
	// Now draw trinagles
	glDrawElements( GL_TRIANGLES, //mode
                  50*3,  //count, ie. how many indices
                  GL_UNSIGNED_INT, //type of the index array
                  0);
	// Thank you, we are done with the vbo
	glDisableClientState(GL_VERTEX_ARRAY);
}

/// Returns the origin coordinates (X) for this region.  Accessors only, as we do not wish to let anyone edit these variables
/*int Tree::getOriginX()
{
	return origin_x;
}

/// Returns the origin coordinates (Y) for this region.  Accessors only, as we do not wish to let anyone edit these variables
int Tree::getOriginY()
{
	return origin_y;
}*/