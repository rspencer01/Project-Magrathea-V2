#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <region.h>
#include <game.h>

Region::Region(int x, int y,Game* parent) : Object(Vector3(x,0.f,y),parent)
{
	printf("New region at %d %d\n",x,y);
	initialiseTriangles();
	tree = new Tree(x,(int)game->getTerrainBit(x,y),y,parent);
}

void Region::initialiseTriangles()
{
  clearTriangleData();
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(REGION_SIZE+1);y++)
		for (int x = 0; x<(REGION_SIZE+1);x++)
		{
      addPoint(Vector3(x,
			                 game->getTerrainBit(x+position.x,y+position.z),
			                 y));
		}
	
  // Populate one triangle (for now) per block
	for (int y = 0; y<REGION_SIZE;y++)
		for (int x = 0; x<REGION_SIZE;x++)
		{
      addTriangle(y*(REGION_SIZE+1) + x,
			            (y+1)*(REGION_SIZE+1) + x,
			            y*(REGION_SIZE+1) + (x+1));
		}
  pushTriangleData();
}

void Region::Render()
{
  Object::Render();
	tree->Render();
}

float Region::getOriginX()
{
  return position.x;
}
float Region::getOriginY()
{
  return position.z;
}
