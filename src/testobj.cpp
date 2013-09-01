#include <testobj.h>
#include <images.h>

TestObj::TestObj(Game* parent) : Object(Vector3(0,0,0),parent)
{
  clearTriangleData(4,4);
  addPoint(0,Vector3(-1,-1,0),Vector3(1,0,1),0,0,1);
  addPoint(1,Vector3(1,-1,0),Vector3(1,0,1),1,0,0);
  addPoint(2,Vector3(0,1,0),Vector3(1,0,1),1,1,0);
  addPoint(3,Vector3(0,1,1),Vector3(1,0,1),0,0,1);
  addTriangle(0,0,1,2);
  addTriangle(1,0,2,3);
  addTriangle(2,0,1,3);
  addTriangle(3,1,2,3);
  pushTriangleData();
}