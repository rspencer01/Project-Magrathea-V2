#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  textureNumber = textureFromRAW("../assets/Sky7.raw");
  clearTriangleData(22,21);
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

  sun = new Sun(Vector3(0,0,0),parent);
}

void Sky::Render(int refreshTime)
{
  Object::Render(refreshTime);
  sun->Render(refreshTime);
}

Sun::Sun(Vector3 pos,Game* parent) : Object(pos,parent)
{
  centre = pos;
  theta = 0;

  clearTriangleData(20,20);
  for(int i = 0;i<20;i++)
  {
    addPoint(i,Vector3(50*sin(i*3.1415*2/20),500,50*cos(i*3.1415*2/20)),
      Vector3(0,1,0),1,1,1);
    editTextureCoord(i,0.1+0.05*sin(i*3.1415*2/20),0.1+0.05*cos(i*3.1415*2/20));
  }
  for(int i = 1;i<19;i++)
    addTriangle(i,0,i,i+1);
  pushTriangleData();
}

void Sun::Render(int refreshTime)
{
  theta += refreshTime / 1000.0 *3.1415*2*2.0/600.0;
/*  rotate(Vector3(cos(refreshTime / 1000.0 *3.1415*2*2.0/600.0),sin(refreshTime / 1000.0 *3.1415*2*2.0/600.0),0),
         Vector3(sin(refreshTime / 1000.0 *3.1415*2*2.0/600.0),cos(refreshTime / 1000.0 *3.1415*2*2.0/600.0),0));
  updateTriangleData();*/
  Object::Render(refreshTime);
}