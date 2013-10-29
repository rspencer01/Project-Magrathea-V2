#include <stdio.h>
#include <math.h>
#include <cloud.h>

/// Initialises the cloud at the position, and constructs it
Cloud::Cloud(Vector3 pos,Game* g) : Object(pos,g)
{
  textureSize = 300;
  data = NULL;
  coverage = 1;
  initialiseTriangles();
  updateTexture();
  drift = randomVector()*0.1;
  drift.y = 0;
  offset = randomVector();
}

void Cloud::initialiseTriangles()
{
  clearTriangleData(4,2);
  addPoint(0,Vector3(-2000,0,-2000),Vector3(0,1,0),1,1,1);
  editTextureCoord(0,0,0);
  addPoint(1,Vector3(-2000,0,2000),Vector3(0,1,0),1,1,1);
  editTextureCoord(1,1,0);
  addPoint(2,Vector3(2000,0,2000),Vector3(0,1,0),1,1,1);
  editTextureCoord(2,1,1);
  addPoint(3,Vector3(2000,0,-2000),Vector3(0,1,0),1,1,1);
  editTextureCoord(3,0,1);
  addTriangle(0,0,1,3);
  addTriangle(1,1,2,3);
  pushTriangleData();
}

void Cloud::updateTexture()
{
  if (data==NULL)
    data = new unsigned char [textureSize*textureSize*4];
  if (textureNumber == -1)
    textureNumber = newTexture(true);
  for (int i =0;i<textureSize;i++)
    for (int j =0;j<textureSize;j++)
    {
      int ind = i*textureSize+j;
      float p = perlinNoise(i/(textureSize/8.0) + offset.x,
                            j/(textureSize/8.0) + offset.z,
                            4,0.97);
      // Make p more pronounced.
      p-=0.2;p*=2.5;

      if (p>1)p = 1;
      if (p<=0) p = 0.01;
      p *= coverage;

      float d = perlinNoise(i/(textureSize/4.0) + offset.x + 20,
                            j/(textureSize/4.0) + offset.z + 20,
                            3,0.98);
      d/=2;
      d *= p;
      d = 1-d;

      p = 0.5 * (sin((p-0.5)*3.1415)+1);

      data[ind*4  ] = d*255;
      data[ind*4+1] = d*255;
      data[ind*4+2] = d*255;
      data[ind*4+3] = p*255;
    }
    
  glBindTexture(GL_TEXTURE_2D,textureNumber);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize, textureSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Cloud::Render(int refreshTime, Vector3* cameraPos)
{
  position = position+drift*refreshTime/1000.0;
  updateMatrix();
  Object::Render(refreshTime,cameraPos);
}