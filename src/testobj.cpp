#include <testobj.h>
#include <images.h>

TestObj::TestObj(Game* parent) : Object(Vector3(0,0,0),parent)
{
  clearTriangleData(11,7);
  addPoint(0,Vector3(-1,-1,0),Vector3(1,0,1),0,0,1);
  addPoint(1,Vector3(1,-1,0),Vector3(1,0,1),1,0,0);
  addPoint(2,Vector3(0,1,0),Vector3(1,0,1),1,1,0);
  addPoint(3,Vector3(0,1,1),Vector3(1,0,1),0,0,1);
  addTriangle(0,0,1,2);
  addTriangle(1,0,2,3);
  addTriangle(2,0,1,3);
  addTriangle(3,1,2,3);
  addPoint(4,Vector3(-10,-10,-5),Vector3(1,0,1),0,0,1);
  addPoint(5,Vector3(-10,10,-5),Vector3(1,0,1),0,1,1);
  addPoint(6,Vector3(10,-10,-5),Vector3(1,0,1),1,1,1);
  addPoint(7,Vector3(10,10,-5),Vector3(1,0,1),0,0,1);
  addTriangle(4,4,5,6);
  addTriangle(5,7,5,6);

  addPoint(8,Vector3(-3,0,3),Vector3(1,0,1),1,0,1);
  addPoint(9,Vector3(-1,0,3),Vector3(1,0,1),0,1,1);
  addPoint(10,Vector3(-2,2,3),Vector3(1,0,1),1,1,1);
  addTriangle(6,8,9,10);
  

  pushTriangleData();
}