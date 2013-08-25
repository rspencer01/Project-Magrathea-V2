#include <GL\glew.h>
#include <GL\glut.h>

#include <stdio.h>
#include <object.h>

Object::Object(Vector3 pos,Game* g)
{
  position = pos;
  game = g;
  buffersInitialised = false;
}

Object::~Object()
{
  if (buffersInitialised)
  {
	glDeleteBuffersARB(1,&vertexVBO);
	glDeleteBuffersARB(1,&indexVBO);
  }
}

Vector3 Object::getPosition()
{
  return position;
}

void Object::Render()
{
	
	if (buffersInitialised)
	{
		// We are passing vertices ...
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBufferARB(GL_ARRAY_BUFFER,vertexVBO);
		glVertexPointer( 3, GL_FLOAT, 0, 0);
		// ... and indexes
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,indexVBO);
		// Now draw trinagles
		glDrawElements( GL_TRIANGLES, //mode
					  numberOfTriangles*3,  //count, ie. how many indices
					  GL_UNSIGNED_INT, //type of the index array
					  0);
		// Thank you, we are done with the vbo
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void Object::clearTriangleData()
{
  // Clear all the data and the buffers (if required)
  triDat.clear();
  posDat.clear();
  if (buffersInitialised)
  {
	glDeleteBuffersARB(1,&vertexVBO);
	glDeleteBuffersARB(1,&indexVBO);
  }
}

void Object::addPoint(Vector3 pt)
{
	// Point is relative to the position of the object
	pt = pt + position;
	posDat.push_back(pt.x);
	posDat.push_back(pt.y);
	posDat.push_back(pt.z);
}

void Object::addTriangle(int a,int b, int c)
{
	triDat.push_back(a);
	triDat.push_back(b);
	triDat.push_back(c);
}

void Object::pushTriangleData()
{
	// Load in the data for points
	float* a = new float[posDat.size()];
	for (unsigned int i = 0; i<posDat.size();i++)
		a[i] = posDat[i];
	// Now make a buffer...
	glGenBuffersARB(1,&vertexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, vertexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, posDat.size()*sizeof(float), a,GL_STATIC_DRAW);
	// We are done with this data, so free it, please.
	delete a;

	//Load in the data for triangles
	int* b = new int[triDat.size()];
	for (unsigned int i = 0; i<triDat.size();i++)
		b[i] = triDat[i];
	// Now make a buffer...
	glGenBuffersARB(1,&indexVBO);
	// set it as the current one,
	glBindBufferARB(GL_ARRAY_BUFFER, indexVBO);
	// ... and blit the data in.
	glBufferDataARB(GL_ARRAY_BUFFER, triDat.size()*sizeof(float),b,GL_STATIC_DRAW);
	// We are done with this data, so free it, please.
	delete b;

	// Finally set the variables that need setting
	buffersInitialised = true;
	numberOfTriangles = triDat.size()/3;
}