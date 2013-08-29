#include <testobj.h>
#include <images.h>

TestObj::TestObj(Game* parent) : Object(Vector3(0,0,0),parent)
{
	loadFromOBJFile("../assets/full019.obj");
  textureNumber = textureFromBMP("../assets/funnyfeeling.bmp");
}