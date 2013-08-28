#include <math.h>
#include <sky.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  clearTriangleData(12,10);
	for (int y = 0; y<11;y++)
	{
		addPoint(y,
             Vector3(1000.f*(float)sin(y/5.f*3.1415),
						 -1.f,
						 1000.f*(float)cos(y/5.f*3.1415)),
             Vector3(0,1,0),
             0.4f,0.4f,1.f);
	}
	addPoint(11,Vector3(0.f,1000.f,0.f),Vector3(0,1,0),0.8f,0.8f,0.8f);
	
	for (int y = 0; y<10;y++)
		addTriangle(y,y,(y+1),11);

	// And save
	pushTriangleData();

}
