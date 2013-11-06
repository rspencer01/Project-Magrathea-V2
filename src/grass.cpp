#include <stdio.h>
#include <grass.h>
#include <noise.h>

// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint grassTextureNumber = (GLuint)-1;
// Where is the texture actually stored?
const char* grassName = "../assets/grass2.tga";

// We only want to load this texture once, if we can reload.  Remember the handle for it.
GLuint grassTextureNumber2 = (GLuint)-1;
// Where is the texture actually stored?
const char* grassName2 = "../assets/grass.tga";


Grass::Grass(Vector3 pos, Vector3 norm, Game* parent) : Object(pos,parent)
{

  // If we have yet to load the texture, do it
  if (grassTextureNumber == (GLuint)-1)
	  grassTextureNumber = textureFromTGA(grassName,true);
  // If we have yet to load the texture, do it
  if (grassTextureNumber2 == (GLuint)-1)
	  grassTextureNumber2 = textureFromTGA(grassName2,true);

  // And set it as this object's texture
  if (random(pos.x+pos.y*10000)>0.2)
    textureNumber = grassTextureNumber;
  else
    textureNumber = grassTextureNumber2;

  
  // 8 points and 4 triangles
  clearTriangleData(24,6);
  numberOfPoints = numberOfTriangles = 0;
  makeBunch(Vector3(0,0,0));
 
  rotate(randomVector().cross(norm),norm);

  updateMatrix();
  pushTriangleData();
}

void Grass::makeBunch(Vector3 position)
{
  // Get a random vector in the xz plane to orient this grass
  Vector3 horis = Vector3(1,0,0);
  horis.normalise();
  Vector3 vert = horis.cross(Vector3(0,1,0));
  
  addPoint(numberOfPoints,horis                   ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,0);
  numberOfPoints++;
  addPoint(numberOfPoints,horis+Vector3(0,1,0)*0.5    ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,1);
  numberOfPoints++;
  addPoint(numberOfPoints,horis*-1                ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,0);
  numberOfPoints++;
  addPoint(numberOfPoints,horis*-1+Vector3(0,1,0)*0.5 ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,1);
  numberOfPoints++;
  addTriangle(numberOfTriangles,numberOfPoints-4,numberOfPoints-3,numberOfPoints-2);
  numberOfTriangles++;
  addTriangle(numberOfTriangles,numberOfPoints-3,numberOfPoints-2,numberOfPoints-1);
  numberOfTriangles++;


  addPoint(numberOfPoints,vert*0.866+horis*0.5    ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,0);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*0.866+horis*0.5 +Vector3(0,1,0)*0.5    ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,1);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*-0.866-horis*0.5                ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,0);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*-0.866-horis*0.5+Vector3(0,1,0)*0.5 ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,1);
  numberOfPoints++;
  addTriangle(numberOfTriangles,numberOfPoints-4,numberOfPoints-3,numberOfPoints-2);
  numberOfTriangles++;
  addTriangle(numberOfTriangles,numberOfPoints-3,numberOfPoints-2,numberOfPoints-1);
  numberOfTriangles++;

  addPoint(numberOfPoints,vert*0.866+horis*-0.5    ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,0);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*0.866+horis*-0.5 +Vector3(0,1,0)*0.5    ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,0,1);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*-0.866+horis*0.5                ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,0);
  numberOfPoints++;
  addPoint(numberOfPoints,vert*-0.866+horis*0.5+Vector3(0,1,0)*0.5 ,Vector3(0,1,0),1,1,1);
  editTextureCoord(numberOfPoints,1,1);
  numberOfPoints++;
  addTriangle(numberOfTriangles,numberOfPoints-4,numberOfPoints-3,numberOfPoints-2);
  numberOfTriangles++;
  addTriangle(numberOfTriangles,numberOfPoints-3,numberOfPoints-2,numberOfPoints-1);
  numberOfTriangles++;

}

void Grass::Render(int refreshTime, Vector3* cameraPos)
{
  if ((*cameraPos - position).magnitude()<10)
    Object::Render(refreshTime,cameraPos);
}