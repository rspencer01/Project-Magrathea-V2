#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <object.h>

/// @param pos The position of this object in gamespace
/// @param g   The game to which this object belongs
Object::Object(Vector3 pos,Game* g)
{
  position = pos;
  game = g;
  buffersInitialised = false;
  vertexData = NULL;
  triDat = NULL;
  textureNumber = -1;
}

/// Frees the data used by this object (esp the buffers in the GPU)
Object::~Object()
{
  if (vertexData!=NULL)
    delete vertexData;
  if (triDat!=NULL)
    delete triDat;
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
  	glDeleteBuffersARB(1,&indexVBO);
  }
}

/// Accesses the position of this object
Vector3 Object::getPosition()
{
  return position;
}

/// Renders this object to the screen, using the VBOs that were 
/// initialised using the addPoint, addTriangle and pushTriangleData
/// functions
void Object::Render()
{
  // Only do something if we have data	
	if (buffersInitialised)
	{

		// We are passing vertices ...
		glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
		if (textureNumber!=-1)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D,textureNumber);
		}
		glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
		glVertexPointer( 3, GL_FLOAT, sizeof(VertexDatum), 0);
        glColorPointer( 3, GL_FLOAT, sizeof(VertexDatum), (void*)(6*sizeof(float)));
		glTexCoordPointer(2,GL_FLOAT,sizeof(VertexDatum),(void*)(9*sizeof(float)));
		// ... and indexes
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
		// Now draw trinagles
		glDrawElements( GL_TRIANGLES, //mode
					  numberOfTriangles*3,  //count, ie. how many indices
					  GL_UNSIGNED_INT, //type of the index array
					  0);
		// Thank you, we are done with the vbo
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/// Reset the data.  Clear the internal arrays, and the GPU arrays.
/// Reserve space for p point and t triangles
/// @param p Number of points
/// @param t Number of triangles
void Object::clearTriangleData(int p, int t)
{
  // Clear all the data and the buffers (if required)
  if (triDat!=NULL)
    delete triDat;
  if (vertexData!=NULL)
    delete vertexData;
  triDat = new int[t*3];
  vertexData = new VertexDatum[p];
  if (buffersInitialised)
  {
  	glDeleteBuffersARB(1,&vertexVBO);
	  glDeleteBuffersARB(1,&indexVBO);
  }
  numberOfTriangles = t;
  numberOfPoints = p;
}
/// Add a new point to the object.  All points are taken relative to the origin of the object
/// @param i The index of the vertex to change
/// @param point The position of this point, relative to the object origin
/// @param r The red component of the colour
/// @param b The blue component of the colour
/// @param g The green component of the colour
void Object::addPoint(int i,Vector3 point,Vector3 normal, float r, float g, float b)
{
	// Point is relative to the position of the object
	point = point + position;
  // Add it to the internal array
	vertexData[i].px = point.x;
	vertexData[i].py = point.y;
	vertexData[i].pz = point.z;
	vertexData[i].nx = normal.x;
	vertexData[i].ny = normal.y;
	vertexData[i].nz = normal.z;
	vertexData[i].red = r * (normal.dot(Vector3(1,1,0))*0.5+0.5);
	vertexData[i].green = g * (normal.dot(Vector3(1,1,0))*0.5+0.5);
	vertexData[i].blue = b * (normal.dot(Vector3(1,1,0))*0.5+0.5);
	vertexData[i].texx = 0;
	vertexData[i].texy = 0;
//  vertexData[i].alpha = 0.5f;

}

/// Adds a new triangle to the object.  Indexes are the same as the order the points were added
/// @param i The index of the triangle to edit
/// @param a The index of the first point
/// @param b The index of the second point
/// @param c The index of the third point
void Object::addTriangle(int i, int a,int b, int c)
{
  // Add it to the internal array
	triDat[i*3] = a;
	triDat[i*3+1] = b;
	triDat[i*3+2] = c;
}

/// Constructs new VBOs and pushes all the data to the GPU
void Object::pushTriangleData()
{
	// Now make a buffer...
	glGenBuffersARB(1,&vertexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, numberOfPoints*sizeof(VertexDatum),vertexData,GL_STATIC_DRAW);

	// Now make a buffer...
	glGenBuffersARB(1,&indexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, indexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, numberOfTriangles*3*sizeof(float),triDat,GL_STATIC_DRAW);

	// Finally set the variables that need setting
	buffersInitialised = true;
}

void Object::editTextureCoord(int i, float u, float v)
{
	vertexData[i].texx = u;
	vertexData[i].texy = v;
}