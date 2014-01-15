#include <math.h>
#include <sky.h>
#include <images.h>
#include <GL/glut.h>

Sky::Sky(Game* parent) : Object(glm::vec3(),parent)
{
  // The sky has no geometry.  This is just here in case it will in some future point.
  // Should probably also handle clouds here.  That will come later
  sun = new Sun(glm::vec3(),parent);
}

void Sky::Render(int refreshTime, glm::vec3 cameraPos)
{
  //Make sure that the sun is ALWAYS behind everything, by disabling depth testing
  glDepthMask(false);
  sun->Render(refreshTime,cameraPos);
  // Do the fog
  game->mainShader->frameData.fog = 20;
  game->mainShader->frameData.fogColour[0] = 1;
  game->mainShader->frameData.fogColour[1] = 1;
  game->mainShader->frameData.fogColour[2] = 1;
  game->mainShader->frameData.fogColour[3] = 1;
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
  position = cameraPos;
  theta += refreshTime / 1000.f *3.1415f*2*2.f / 600.f;

  game->mainShader->frameData.sunDirection[0] = sin(theta);
  game->mainShader->frameData.sunDirection[1] = cos(theta);
  game->mainShader->frameData.sunDirection[2] = 0;

  rotate(glm::vec3(cos(theta),-sin(theta),0),
         glm::vec3(sin(theta),cos(theta),0));
  updateTriangleData();
  // We want to be fully lit.
  game->mainShader->frameData.sunIntensity=1.0;
  Object::Render(refreshTime,cameraPos);
  // Then light the rest as per usual.
  if (cos(theta)>0)
    game->mainShader->frameData.sunIntensity=cos(theta);
  else
    game->mainShader->frameData.sunIntensity=0;
}
