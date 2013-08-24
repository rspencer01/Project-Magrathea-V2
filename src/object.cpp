#include <object.h>

Object::Object(int x, int y,int z,Game* g)
{
	origin_x = x;
	origin_y = y;
	origin_z = z;
	game = g;
}

Object::~Object()
{
}
