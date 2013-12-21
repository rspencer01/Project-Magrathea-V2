#include <stdio.h>
#include <math.h>
#include <cloud.h>
#include <gtx/random.hpp>


/// Initialises the cloud at the position, and constructs it
Cloud::Cloud(glm::vec3 pos,Game* g) : Object(pos,g)
{
  textureSize = 300;
  data = NULL;
  coverage = 1;
  initialiseTriangles();
  updateTexture();
  drift = glm::sphericalRand(0.1f);
  drift.y = 0;
  offset = glm::sphericalRand(1.f);
}

void Cloud::initialiseTriangles()
{
  clearTriangleData(4,2);
  addPoint(0,glm::vec3(-2000,0,-2000),glm::vec3(0,1,0),1,1,1);
  editTextureCoord(0,0,0);
  addPoint(1,glm::vec3(-2000,0,2000),glm::vec3(0,1,0),1,1,1);
  editTextureCoord(1,1,0);
  addPoint(2,glm::vec3(2000,0,2000),glm::vec3(0,1,0),1,1,1);
  editTextureCoord(2,1,1);
  addPoint(3,glm::vec3(2000,0,-2000),glm::vec3(0,1,0),1,1,1);
  editTextureCoord(3,0,1);
  addTriangle(0,0,1,3);
  addTriangle(1,1,2,3);
  pushTriangleData();
}

void Cloud::updateTexture()
{
  if (data==NULL)
    data = new unsigned char [textureSize*textureSize*4];
  if (textureNumber == 0) //Empty Texture are zero
    textureNumber = newTexture(true);
  for (int i =0;i<textureSize;i++)
    for (int j =0;j<textureSize;j++)
    {
      int ind = i*textureSize+j;
      float p = perlinNoise(i/(textureSize/8.f) + offset.x,
                            j/(textureSize/8.f) + offset.z,
                            4,0.97f);
      // Make p more pronounced.
      p-=0.2f;p*=2.5f;

      if (p>1)p = 1;
      if (p<=0) p = 0.01f;
      p *= coverage;

      float d = perlinNoise(i/(textureSize/4.f) + offset.x + 20,
                            j/(textureSize/4.f) + offset.z + 20,
                            3,0.98f);
      d/=2;
      d *= p;
      d = 1-d;

      p = 0.5f * (float)(sin((p-0.5)*3.1415)+1);

      data[ind*4  ] = (unsigned char)(d*255);
      data[ind*4+1] = (unsigned char)(d*255);
      data[ind*4+2] = (unsigned char)(d*255);
      data[ind*4+3] = (unsigned char)(p*255);
    }
    
  glBindTexture(GL_TEXTURE_2D,textureNumber);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize, textureSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Cloud::Render(int refreshTime, glm::vec3 cameraPos)
{
  position = position+drift*(float)refreshTime/1000.f;
  updateMatrix();
  Object::Render(refreshTime,cameraPos);
}
