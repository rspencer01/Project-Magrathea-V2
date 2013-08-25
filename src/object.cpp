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
  printf("Object data cleared\n");
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
	printf("Added point %f %f %f\n",pt.x,pt.y,pt.z);
	pt = pt + position;
	posDat.push_back(pt.x);
	posDat.push_back(pt.y);
	posDat.push_back(pt.z);
}

void Object::addTriangle(int a,int b, int c)
{
	printf("Added triangle %d %d %d\n",a,b,c);
	triDat.push_back(a);
	triDat.push_back(b);
	triDat.push_back(c);
}

void Object::pushTriangleData()
{
	printf("Object data pushed\n");
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
	buffersInitialised = true;
	numberOfTriangles = triDat.size()/3;
}