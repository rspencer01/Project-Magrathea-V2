#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <region.h>
#include <game.h>

Region::Region(int x, int y,Game* parent)
{
	printf("New region at %d %d\n",x,y);
	origin_x = x;
	origin_y = y;
    game = parent;
    buffersInitialised = false;
	initialiseTriangles();
	tree = new Tree(origin_x,origin_y,game->getTerrainBit(origin_x,origin_y),parent);
}

Region::~Region()
{
	if (buffersInitialised)
	{
		glDeleteBuffersARB(1,&vertexVBO);
		glDeleteBuffersARB(1,&indexVBO);
	}
}

void Region::initialiseTriangles()
{
	// This will hold the vertex position data
	float* triangleData = new float[(REGION_SIZE+1)*(REGION_SIZE+1)*3];
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(REGION_SIZE+1);y++)
		for (int x = 0; x<(REGION_SIZE+1);x++)
		{
			triangleData[(y*(REGION_SIZE+1)+x)*3    ] = (float)(origin_x+x);
			triangleData[(y*(REGION_SIZE+1)+x)*3 + 1] = game->getTerrainBit(x+origin_x,y+origin_y);
			triangleData[(y*(REGION_SIZE+1)+x)*3 + 2] = (float)(origin_y+y);
		}
	// Now make a buffer...
	glGenBuffersARB(1,&vertexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, (REGION_SIZE+1)*(REGION_SIZE+1)*3*sizeof(float), triangleData,GL_STATIC_DRAW);
	// We are done with this data, so free it, please.
	delete[] triangleData;

	// As above, each of the REGION_SIZE*REGION_SIZE gets 3 vertices
	int* indexData = new int[REGION_SIZE*REGION_SIZE*3];
	// Populate one triangle (for now) per block
	for (int y = 0; y<REGION_SIZE;y++)
		for (int x = 0; x<REGION_SIZE;x++)
		{
			indexData[(y*REGION_SIZE+x)*3    ] = y*(REGION_SIZE+1) + x;
			indexData[(y*REGION_SIZE+x)*3 + 1] = (y+1)*(REGION_SIZE+1) + x;
			indexData[(y*REGION_SIZE+x)*3 + 2] = y*(REGION_SIZE+1) + (x+1);
		}
	// Make another buffer...
	glGenBuffersARB(1,&indexVBO);
	// an element array buffer (which we mount),
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
	// ... and put the data in.
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, REGION_SIZE*REGION_SIZE*3*sizeof(int), indexData,GL_STATIC_DRAW);
	// Then again, free this up
	delete[] indexData;	

	// Now we have initialised these things, so they can be released if required
	buffersInitialised = true;
}

void Region::Render()
{
	// We are passing vertices ...
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
	glVertexPointer( 3, GL_FLOAT, 0, 0);
	// ... and indexes
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
	// Now draw trinagles
	glDrawElements( GL_TRIANGLES, //mode
                  REGION_SIZE*REGION_SIZE*3,  //count, ie. how many indices
                  GL_UNSIGNED_INT, //type of the index array
                  0);
	// Thank you, we are done with the vbo
	glDisableClientState(GL_VERTEX_ARRAY);
	tree->Render();
}

/// Returns the origin coordinates (X) for this region.  Accessors only, as we do not wish to let anyone edit these variables
int Region::getOriginX()
{
	return origin_x;
}

/// Returns the origin coordinates (Y) for this region.  Accessors only, as we do not wish to let anyone edit these variables
int Region::getOriginY()
{
	return origin_y;
}