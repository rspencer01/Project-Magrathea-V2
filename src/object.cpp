#include <stdio.h>
#include <object.h>

Object::Object(Vector3 pos,Game* g)
{
  position = pos;
	game = g;
}

Object::~Object()
{
  printf("DESTROED OBJECT\n");
}

Vector3 Object::getPosition()
{
  return position;
}
