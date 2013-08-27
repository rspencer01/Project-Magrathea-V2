#include <stdio.h>
#include <grass.h>
#include <noise.h>

Grass::Grass(Vector3 pos, Vector3 norm, Game* parent) : Object(pos,parent)
{
  norm = norm;
  Vector3 rnd = Vector3(random((int)pos.x)-0.5f,0,random((int)pos.z)-0.5f);
  rnd.normalise();

  clearTriangleData(8,4);
  addPoint(0,rnd.cross(norm)-norm,0,0.5f,0);
  addPoint(1,rnd.cross(norm)+norm/3,0,0.5f,0);
  addPoint(2,rnd.cross(norm)*-1-norm,0,0.5f,0);
  addPoint(3,rnd.cross(norm)*-1+norm/3,0,0.5f,0);
  addTriangle(0,0,1,2);
  addTriangle(1,1,2,3);
  rnd = rnd.cross(norm);
  addPoint(4,rnd.cross(norm)-norm,0,0.5f,0);
  addPoint(5,rnd.cross(norm)+norm/3,0,0.5f,0);
  addPoint(6,rnd.cross(norm)*-1-norm,0,0.5f,0);
  addPoint(7,rnd.cross(norm)*-1+norm/3,0,0.5f,0);
  addTriangle(2,4,5,6);
  addTriangle(3,5,6,7);
 
  pushTriangleData();
}
