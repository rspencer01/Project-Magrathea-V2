#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(Vector3(0,0,0),parent)
{
  sun = new Sun(Vector3(0,0,0),parent);
  stars = new Stars(parent);
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
  theta = 0.f;
}

inline float k(float x){return -cos(x*3.1415f)/2.f+0.5f;}
 

void Sky::Render(int refreshTime, Vector3* cameraPos)
{
  // Make sure that the sun is ALWAYS behind everything, by disabling depth testing
  glDepthMask(false);
  // Remove all the lighting stuff
  game->currentShader->setInt("doLighting",0);
  // Move the sky dome
  setPosition(*cameraPos);
  // Update the colour...
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;
  float l = pow(3.0*(1.0 - k(k(k(theta/3.1415))))/4.0 + 0.25,1.4);
  colour[0] = l*( k(k(k(sin(theta/2.f))))/20.0 + 0.4);
  colour[1] = l*( 0.6 - k(k(k(sin(theta/2.f))))/9.0);
  colour[2] = l*1.0;
  // Render stuff
  Object::Render(refreshTime,cameraPos);
  sun->Render(refreshTime,cameraPos);
  stars->Render(refreshTime,cameraPos);
  // Reinstate rendering
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
  game->currentShader->setFloat("sunIntensity",pow(3.0*(1.0 - k(k(k(theta/3.1415))))/4.0 + 0.25,1.4));
}

Stars::Stars(Game* parent) : Object(Vector3(0,0,0),parent)
{
  float radius = 400;
  float starSize = 1.22;
  float numStars = 2000;
  clearTriangleData(numStars*6,numStars*5);
  for (int j = 0;j<numStars;j++)
  {
    float siz = std::max((random(j)*starSize)*(random(j)*starSize)*(random(j)*starSize),starSize/5.f);
    Vector3 po = randomVector()*radius;
    Vector3 up = randomVector().cross(po).normal()*siz;
    Vector3 right = po.cross(up).normal()*siz;
    for(int i = j*6;i<(j+1)*6;i++)
    {
      addPoint(i,po+up*sin(i/6.0*3.1415*2)+right*cos(i/6.0*3.1415*2),Vector3(0,1,1),1,1,1);
      editTextureCoord(i,(float)(0.5+0.5*sin(i*3.1415*2/6)),(float)(0.5+0.5*cos(i*3.1415*2/6)));
    }
    for(int i = 0;i<5;i++)
      addTriangle(j*5+i,j*6,j*6+i,j*6+i+1);
  }
  pushTriangleData();
  textureNumber = textureFromTGA("../assets/sun.tga",true);
  theta = 0.f;
  freeze();
}

void Stars::Render(int refreshTime,Vector3* cameraPos)
{
  setPosition(*cameraPos);
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;
  Vector3 inc = Vector3(0,0,1);
  Vector3 right = Vector3(1,0,0).cross(inc);
  Vector3 up = inc.cross(right);
  rotate(inc,up*sin(-theta)+right*cos(theta));
  float l = 3.0*(1.0 - k(k(k(theta/3.1415))))/4.0 + 0.25;
  colour[3] = k((1-l)*(1-l)*(1-l));
  Object::Render(refreshTime,cameraPos);
}