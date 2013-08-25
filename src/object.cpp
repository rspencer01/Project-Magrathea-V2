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