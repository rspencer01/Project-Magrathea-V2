#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  textureNumber = textureFromTGA("../assets/sky.tga",true);
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
	addPoint(21,Vector3(1000.f*(float)sin(21/10.f*3.1415),
						  2000.f,
						  1000.f*(float)cos(21/10.f*3.1415)),
              Vector3(0,1,0),
              1.f,1.f,1.f);
  editTextureCoord(21,0.5,0.5);
	
	for (int y = 0; y<20;y++)
		addTriangle(y,y,(y+1),21);

  // And save
	pushTriangleData();

  sun = new Sun(Vector3(0,0,0),parent);
}

void Sky::Render(int refreshTime, Vector3* cameraPos)
{
  glDepthMask(false);
  sun->Render(refreshTime,cameraPos);
  glDepthMask(true);
  game->currentShader->setFloat("sunIntensity",1.0);
  //Object::Render(refreshTime,cameraPos);
  
}

Sun::Sun(Vector3 pos,Game* parent) : Object(pos,parent)
{
  // Get the texture
  textureNumber = textureFromTGA("../assets/sun.tga",true);

  int SUN_SIZE = 20;
  centre = pos;
  theta = 0;

  clearTriangleData(20,20);
  for(int i = 0;i<20;i++)
  {
    addPoint(i,Vector3(2*SUN_SIZE*sin(i*3.1415*2/20),500,2*SUN_SIZE*cos(i*3.1415*2/20)),
      Vector3(0,1,0),1,1,1);
    editTextureCoord(i,0.5+0.5*sin(i*3.1415*2/20),0.5+0.5*cos(i*3.1415*2/20));
  }
  for(int i = 1;i<19;i++)
    addTriangle(i,0,i,i+1);
  pushTriangleData();
}

void Sun::Render(int refreshTime,Vector3* cameraPos)
{
  position = *cameraPos;
  theta += refreshTime / 1000.0 *3.1415*2*2.0 / 600.0;
  float sunDir[3];
  sunDir[0] = sin(theta);
  sunDir[1] = cos(theta);
  sunDir[2] = 0;
  game->currentShader->setVec3("sunDirection",sunDir);
  rotate(Vector3(cos(theta),-sin(theta),0),
         Vector3(sin(theta),cos(theta),0));
  updateTriangleData();
  // We want to be fully lit.
  
  Object::Render(refreshTime,cameraPos);
  // Then light the rest as per usual.
  if (cos(theta)>0)
    game->currentShader->setFloat("sunIntensity",cos(theta));
  else
    game->currentShader->setFloat("sunIntensity",0);
}
