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
