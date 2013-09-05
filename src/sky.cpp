#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  textureNumber = textureFromRAW("../assets/Sky7.raw");
  clearTriangleData(22,20);
	for (int y = 0; y<21;y++)
	{
		addPoint(y,
             Vector3(1000.f*(float)sin(y/10.f*3.1415),
						 -100.f,
						 1000.f*(float)cos(y/10.f*3.1415)),
             Vector3(0,1,0),
             1.f,1.f,1.f);
    editTextureCoord(y,0.5+0.5*sin(-y/10.0*3.1415),0.5+0.5*cos(-y/10.0*3.1415));
	}
	addPoint(21,Vector3(0.f,1000.f,0.f),Vector3(0,1,0),1.f,1.f,1.f);
  editTextureCoord(21,0.5,0.5);
	
	for (int y = 0; y<20;y++)
		addTriangle(y,y,(y+1),21);

	// And save
	pushTriangleData();

}

