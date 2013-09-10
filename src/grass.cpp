#include <stdio.h>
#include <grass.h>
#include <noise.h>

Grass::Grass(Vector3 pos, Vector3 norm, Game* parent,ShaderProgram* s) : Object(pos,parent,s)
{
  // Get a random vector in the xz plane to orient this grass
  Vector3 rnd = Vector3(random((int)pos.x)-0.5f,0,random((int)pos.z)-0.5f);
  rnd.normalise();

  // 8 points and 4 triangles
  clearTriangleData(8,4);
  // Construct the on cross
  addPoint(0,rnd.cross(norm)-norm,Vector3(0,1,0),0,0.5f,0);
  addPoint(1,rnd.cross(norm)+norm/3,Vector3(0,1,0),0,0.5f,0);
  addPoint(2,rnd.cross(norm)*-1-norm,Vector3(0,1,0),0,0.5f,0);
  addPoint(3,rnd.cross(norm)*-1+norm/3,Vector3(0,1,0),0,0.5f,0);
  addTriangle(0,0,1,2);
  addTriangle(1,1,2,3);
  // Do the same after turning the rnd vector 90%
  rnd = rnd.cross(norm);
  addPoint(4,rnd.cross(norm)-norm,Vector3(0,1,0),0,0.5f,0);
  addPoint(5,rnd.cross(norm)+norm/3,Vector3(0,1,0),0,0.5f,0);
  addPoint(6,rnd.cross(norm)*-1-norm,Vector3(0,1,0),0,0.5f,0);
  addPoint(7,rnd.cross(norm)*-1+norm/3,Vector3(0,1,0),0,0.5f,0);
  addTriangle(2,4,5,6);
  addTriangle(3,5,6,7);
 
  pushTriangleData();
}
