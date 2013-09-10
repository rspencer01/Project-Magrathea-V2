#include <math.h>
#include <bird.h>


// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint birdTextureNumber = (GLuint)-1;
// Where is the texture actually stored?
const char* birdtextureName = "../assets/bird2.bmp";

Bird::Bird(Vector3 position, Game* game) : Object(position,game)
{
  initialiseTriangles();
    // If we have yet to load the texture, do it
  if (birdTextureNumber == (GLuint)-1)
	  birdTextureNumber = textureFromBMP(birdtextureName);
  // And set it as this object's texture
  textureNumber = birdTextureNumber;
  theta = 3.141592 * random((int)this+position.x+position.y+position.x*position.z);
  turnCoeff = 0.2*(random((int)this+position.x+position.y+position.x*position.z+1)-0.5);
  forward = randomVector();
  forward.y = 0;
  forward.normalise();
  velocity = forward;
  upward = Vector3(0,1,0);
}

void Bird::initialiseTriangles()
{
  clearTriangleData(5,2);
  addPoint(0,Vector3(0,0,0),Vector3(0,1,0),1,1,1);
  editTextureCoord(0,0.5,0);
  addPoint(1,Vector3(0.5,0,1),Vector3(0,1,0),1,1,1);
  editTextureCoord(1,1,0.5);
  addPoint(2,Vector3(0.5,0,-1),Vector3(0,1,0),1,1,1);
  editTextureCoord(2,0,0.5);
  addPoint(3,Vector3(1,0,0),Vector3(0,1,0),1,1,1);
  editTextureCoord(3,0.5,1);
  addTriangle(0,0,1,3);
  addTriangle(1,0,2,3);
  pushTriangleData();
}

void Bird::Render(int refreshTime)
{
  Object::Render(refreshTime);

  theta += refreshTime*3.141592*2.0/1000.0 * 0.7;
  dihedral =  -sin(theta) - 1/5.0*sin(theta*2) - 1/25.0*sin(theta*3);
  addPoint(1,Vector3(0.5,sin(dihedral),cos(dihedral)),Vector3(0,1,0),1,1,1);
  addPoint(2,Vector3(0.5,sin(dihedral),-cos(dihedral)),Vector3(0,1,0),1,1,1);

  velocity = velocity - velocity*0.05*refreshTime/1000.0;
  velocity = velocity + Vector3(0,-0.98,0)*refreshTime/1000.0;

  float fs = cos(theta)+1/5.0*cos(theta*2);
  if (fs<0)
    fs = 0;

  velocity = velocity + upward*fs*3.07*refreshTime/1000.0;
  velocity = velocity + forward*fs*0.8*refreshTime/1000.0;

  forward = (forward + forward.cross(upward)*turnCoeff*refreshTime/1000.0).normal();

  setPosition(position + velocity * refreshTime/1000.0);

  updateTriangleData();
  
}
