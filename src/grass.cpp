#include <stdio.h>
#include <grass.h>
#include <noise.h>

Grass::Grass(Vector3 pos, Vector3 norm, Game* parent) : Object(pos,parent)
{
  norm = norm;
  Vector3 rnd = Vector3(random((int)pos.x)-0.5f,0,random((int)pos.z)-0.5f);
  rnd.normalise();

  clearTriangleData();
  addPoint(rnd.cross(norm));
  addPoint(rnd.cross(norm)+norm/3);
  addPoint(rnd.cross(norm)*-1);
  addPoint(rnd.cross(norm)*-1+norm/3);
  addTriangle(0,1,2);
  addTriangle(1,2,3);
  rnd = rnd.cross(norm);
  addPoint(rnd.cross(norm));
  addPoint(rnd.cross(norm)+norm/3);
  addPoint(rnd.cross(norm)*-1);
  addPoint(rnd.cross(norm)*-1+norm/3);
  addTriangle(4,5,6);
  addTriangle(5,6,7);
 
  pushTriangleData();
}
