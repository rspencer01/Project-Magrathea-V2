#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  // The sky has no geometry.  This is just here in case it will in some future point.
  // Should probably also handle clouds here.  That will come later
  sun = new Sun(Vector3(0,0,0),parent);
  float radius = 500;
  clearTriangleData(12,20);
  addPoint(0,Vector3(0,1,0)*radius,Vector3(0,1,0),1,1,1);
  editTextureCoord(0,0,0);
  for (int i = 0;i<5;i++)
  {
    addPoint(i+1,Vector3(sin((63.43)/180*3.1415)*cos(i*3.1415/2.5)     ,cos((63.43)/180*3.1415),sin((63.43)/180*3.1415)*sin(i*3.1415/2.5))*radius,Vector3(0,1,0),1,1,1);
    editTextureCoord(i+1,i/5,i/10);
    addTriangle(i,0,i+1,(i+1)%5 +1);
  }
  addPoint(6,Vector3(0,-1,0)*radius,Vector3(0,-1,0),1,1,1);
  editTextureCoord(6,0,0);
  for (int i = 0;i<5;i++)
  {
    addPoint(i+7,Vector3(sin((63.43)/180*3.1415)*cos((i+0.5)*3.1415/2.5)     ,-cos((63.43)/180*3.1415),sin((63.43)/180*3.1415)*sin((i+0.5)*3.1415/2.5))*radius,Vector3(0,-1,0),1,1,1);
    editTextureCoord(i+7,i/5,i/10);
    addTriangle(i+5,6,i+7,(i+1)%5 + 7);
  }
  for (int i = 0;i<5;i++)
    addTriangle(i+10,i+1,(i+1)%5+1,i + 7);
  for (int i = 0;i<5;i++)
    addTriangle(i+15,i+7,(i+1)%5+7,(i + 1)%5+1);
  
  textureNumber = textureFromTGA("../assets/plainsky.tga",false);
  pushTriangleData();

}

void Sky::Render(int refreshTime, Vector3* cameraPos)
{
  //Make sure that the sun is ALWAYS behind everything, by disabling depth testing
  glDepthMask(false);
  //Remove all the lighting stuff
  game->currentShader->setInt("doLighting",0);
  setPosition(*cameraPos);
  Object::Render(refreshTime,cameraPos);
  sun->Render(refreshTime,cameraPos);
  glDepthMask(true);
  game->currentShader->setInt("doLighting",1);
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
    addPoint(i,Vector3(2*SUN_SIZE*(float)sin(i*3.1415*2/20),500.f,2*SUN_SIZE*(float)cos(i*3.1415*2/20)),
      Vector3(0,1,0),1,1,1);
    editTextureCoord(i,(float)(0.5+0.5*sin(i*3.1415*2/20)),(float)(0.5+0.5*cos(i*3.1415*2/20)));
  }
  for(int i = 1;i<19;i++)
    addTriangle(i,0,i,i+1);
  pushTriangleData();
}

void Sun::Render(int refreshTime,Vector3* cameraPos)
{
  position = *cameraPos;
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;
  float sunDir[3];
  sunDir[0] = sin(theta);
  sunDir[1] = cos(theta);
  sunDir[2] = 0;
  game->currentShader->setVec3("sunDirection",sunDir);

  rotate(Vector3(cos(theta),-sin(theta),0),
         Vector3(sin(theta),cos(theta),0));
  updateTriangleData();
  // We want to be fully lit.
  game->currentShader->setFloat("sunIntensity",1.0);
  Object::Render(refreshTime,cameraPos);
  // Then light the rest as per usual.
  if (cos(theta)>0)
    game->currentShader->setFloat("sunIntensity",cos(theta));
  else
    game->currentShader->setFloat("sunIntensity",0);
}
