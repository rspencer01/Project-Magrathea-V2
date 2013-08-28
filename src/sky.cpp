#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  //textureNumber = textureFromBMP("../assets/sky4.bmp");
  clearTriangleData(12,10);
	for (int y = 0; y<11;y++)
	{
		addPoint(y,
             Vector3(1000.f*(float)sin(y/5.f*3.1415),
						 -1.f,
						 1000.f*(float)cos(y/5.f*3.1415)),
             Vector3(0,1,0),
             0.58f,0.8f,0.86f);
    //editTextureCoord(y,0.5+0.5*sin(y/5.0*3.1415),0.5+0.5*cos(y/5.0*3.1415));
	}
	addPoint(11,Vector3(0.f,1000.f,0.f),Vector3(0,1,0),0.31f,0.68f,0.86f);
  //editTextureCoord(11,0.5,0.5);
	
	for (int y = 0; y<10;y++)
		addTriangle(y,y,(y+1),11);

	// And save
	pushTriangleData();

}

