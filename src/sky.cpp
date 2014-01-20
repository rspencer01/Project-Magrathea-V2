#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>
#include <gtx\random.hpp>

Sky::Sky(Game* parent) : Object(glm::vec3(),parent)
{
  sun = new Sun(glm::vec3(0),parent);
  stars = new Stars(parent);
  float radius = 500;
  clearTriangleData(12,20);
  addPoint(0,glm::vec3(0,1,0)*radius,glm::vec3(0,1,0),1,1,1);
  editTextureCoord(0,0,0);
  for (int i = 0;i<5;i++)
  {
    addPoint(i+1,glm::vec3(sin((63.43)/180*3.1415)*cos(i*3.1415/2.5)     ,cos((63.43)/180*3.1415),sin((63.43)/180*3.1415)*sin(i*3.1415/2.5))*radius,glm::vec3(0,1,0),1,1,1);
    editTextureCoord(i+1,i/5.f,i/10.f);
    addTriangle(i,0,i+1,(i+1)%5 +1);
  }
  addPoint(6,glm::vec3(0,-1,0)*radius,glm::vec3(0,-1,0),1,1,1);
  editTextureCoord(6,0,0);
  for (int i = 0;i<5;i++)
  {
    addPoint(i+7,glm::vec3(sin((63.43)/180*3.1415)*cos((i+0.5)*3.1415/2.5)     ,-cos((63.43)/180*3.1415),sin((63.43)/180*3.1415)*sin((i+0.5)*3.1415/2.5))*radius,glm::vec3(0,-1,0),1,1,1);
    editTextureCoord(i+7,i/5.f,i/10.f);
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
 

void Sky::Render(int refreshTime, glm::vec3 cameraPos)
{
  // Make sure that the sun is ALWAYS behind everything, by disabling depth testing
  glDepthMask(false);
  // Remove all the lighting stuff
  game->mainShader->frameData.doLighting = 0;
  game->mainShader->setFrameData();
  // Move the sky dome
  setPosition(cameraPos);
  // Update the colour...
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;
  float l = pow(3.f*(1.f - k(k(k(theta/3.1415f))))/4.f + 0.25f,1.4f);
  objectData.objectColour[0] = l*( k(k(k(sin(theta/2.f))))/20.f + 0.4f);
  objectData.objectColour[1] = l*( 0.6f - k(k(k(sin(theta/2.f))))/9.f);
  objectData.objectColour[2] = l*1.f;
  updateObjectBO();
  // Render stuff
  //Object::Render(refreshTime,cameraPos);
  sun->Render(refreshTime,cameraPos);

  //stars->Render(refreshTime,cameraPos);
  // Reinstate rendering
  // Do the fog
  game->mainShader->frameData.fog = 16000;
  game->mainShader->frameData.fogColour[0] = 1;
  game->mainShader->frameData.fogColour[1] = 1;
  game->mainShader->frameData.fogColour[2] = 1;
  game->mainShader->frameData.fogColour[3] = 1;
  game->mainShader->frameData.doLighting = 1;
  game->mainShader->setFrameData();
  glDepthMask(true);

}

Sun::Sun(glm::vec3 pos,Game* parent) : Object(pos,parent)
{
  // Get the texture
  textureNumber = textureFromTGA("../assets/sun.tga",true);

  int SUN_SIZE = 20;
  centre = pos;
  theta = 0;

  clearTriangleData(20,20);
  for(int i = 0;i<20;i++)
  {
    addPoint(i,glm::vec3(2*SUN_SIZE*(float)sin(i*3.1415*2/20),500.f,2*SUN_SIZE*(float)cos(i*3.1415*2/20)),
      glm::vec3(0,1,0),1,1,1);
    editTextureCoord(i,(float)(0.5+0.5*sin(i*3.1415*2/20)),(float)(0.5+0.5*cos(i*3.1415*2/20)));
  }
  for(int i = 1;i<19;i++)
    addTriangle(i,0,i,i+1);
  pushTriangleData();
}

void Sun::Render(int refreshTime,glm::vec3 cameraPos)
{
  setPosition(cameraPos);
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;

  game->mainShader->frameData.sunDirection[0] = sin(theta);
  game->mainShader->frameData.sunDirection[1] = cos(theta);
  game->mainShader->frameData.sunDirection[2] = 0;

  rotate(glm::vec3(cos(theta),-sin(theta),0),
         glm::vec3(sin(theta),cos(theta),0));
  updateTriangleData();
  // We want to be fully lit.
  game->mainShader->frameData.sunIntensity=1.0;
  //Object::Render(refreshTime,cameraPos);
  // Then light the rest as per usual.
  game->mainShader->frameData.sunIntensity = pow(3.f*(1.f - k(k(k(theta/3.1415f))))/4.f + 0.25f,1.4f);
  if (cos(theta)>0)
    game->mainShader->frameData.sunIntensity=cos(theta);
  else
    game->mainShader->frameData.sunIntensity=0;
  game->mainShader->setFrameData();
}

Stars::Stars(Game* parent) : Object(glm::vec3(0),parent)
{
  float radius = 400.f;
  float starSize = 1.22f;
  int numStars = 2000;
  clearTriangleData(numStars*6,numStars*5);
  for (int j = 0;j<numStars;j++)
  {
    float siz = std::max((random(j)*starSize)*(random(j)*starSize)*(random(j)*starSize),starSize/5.f);
    glm::vec3 po = glm::sphericalRand(radius);
    glm::vec3 up = glm::normalize(glm::cross(glm::sphericalRand(1.f),po))*siz;
    glm::vec3 right = glm::normalize(glm::cross(po,up))*siz;
    for(int i = j*6;i<(j+1)*6;i++)
    {
      addPoint(i,po+up*(float)sin(i/6.0*3.1415*2)+(float)cos(i/6.0*3.1415*2)*right,glm::vec3(0,1,1),1,1,1);
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

void Stars::Render(int refreshTime,glm::vec3 cameraPos)
{
  setPosition(cameraPos);
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;
  glm::vec3 inc = glm::vec3(0,0,1.f);
  glm::vec3 right = glm::cross(glm::vec3(1.f,0,0),inc);
  glm::vec3 up = glm::cross(inc,right);
  rotate(inc,up*sin(-theta)+right*cos(theta));
  float l = 3.f*(1.f - k(k(k(theta/3.1415f))))/4.f + 0.25f;
  objectData.objectColour[3] = k((1-l)*(1-l)*(1-l));
  updateObjectBO();
  Object::Render(refreshTime,cameraPos);
}
