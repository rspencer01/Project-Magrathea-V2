#include <math.h>
#include <bird.h>
#include <gtx/random.hpp>


// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint birdTextureNumber = 0;
// Where is the texture actually stored?
const char* birdtextureName = "../assets/bird.tga";

Bird::Bird(glm::vec3 position, Game* game) : Object(position,game)
{
  initialiseTriangles();
    // If we have yet to load the texture, do it
  if (birdTextureNumber == 0)
	  birdTextureNumber = textureFromTGA(birdtextureName,false);
  // And set it as this object's texture
  textureNumber = birdTextureNumber;
  theta = 3.141592f * random((int)(position.x+position.y+position.x*position.z));
  turnCoeff = 0.2f*(random((int)(position.x+position.y+position.x*position.z+1))-0.5f);
  forward = glm::sphericalRand(1.0);
  velocity = forward;
  upward = glm::vec3(0,1,0);
}

void Bird::initialiseTriangles()
{
  clearTriangleData(5,2);
  addPoint(0,glm::vec3(0,0,0)   ,glm::vec3(0,1,0),1,1,1);
  editTextureCoord(0,0.5,0);
  addPoint(1,glm::vec3(0.5,0,1) ,glm::vec3(0,1,0),1,1,1);
  editTextureCoord(1,1,0.5);
  addPoint(2,glm::vec3(0.5,0,-1),glm::vec3(0,1,0),1,1,1);
  editTextureCoord(2,0,0.5);
  addPoint(3,glm::vec3(1,0,0)   ,glm::vec3(0,1,0),1,1,1);
  editTextureCoord(3,0.5,1);
  addTriangle(0,0,1,3);
  addTriangle(1,0,2,3);
  pushTriangleData();
}

void Bird::Render(int refreshTime, glm::vec3 cameraPos)
{

  float refreshSeconds = (float)refreshTime/1000.f;
  Object::Render(refreshTime,cameraPos);
  //This is a godforsakenslow bit
  theta    += (float)(refreshSeconds * 3.141592 * 2.0 * 0.7);
  dihedral  = (float)(- (float)sin(theta) - 1/5.0*(float)sin(theta*2) - 1/25.0*(float)sin(theta*3));
  addPoint(1,glm::vec3(0.5,(float)sin(dihedral),(float)cos(dihedral)),glm::vec3(0,1,0),1,1,1);
  addPoint(2,glm::vec3(0.5,(float)sin(dihedral),-(float)cos(dihedral)),glm::vec3(0,1,0),1,1,1);

  velocity = velocity - velocity*0.05f*refreshSeconds;
  velocity = velocity + glm::vec3(0.f,-0.98f,0.f)*refreshSeconds;

  float fs = (float)((float)cos(theta)+1/5.0*(float)cos(theta*2));
  if (fs<0.f)
    fs = 0.f;

  velocity = velocity + upward*fs*3.07f*refreshSeconds;
  velocity = velocity + forward*fs*0.8f*refreshSeconds;

  forward = glm::normalize(forward + glm::cross(forward,upward)*turnCoeff*refreshSeconds);
  forward.y = 0.f;

  setPosition(position + velocity * refreshSeconds);
  rotate(glm::normalize(velocity),upward);

  updateTriangleData();
}
