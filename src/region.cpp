#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <region.h>
#include <game.h>
#include <noise.h>

/// Constructs a new region at the given position
/// @param x The x coordinate of the origin
/// @param y The y coordinate of the origin
/// @param parent The game that this region is in.
Region::Region(int x, int y,Game* parent) : Object(Vector3(x,0.f,y),parent)
{
	printf("New region at %d %d\n",x,y);
	initialiseTriangles();
  for (int ty = 0;y<REGION_SIZE;y++)
    for (int tx = 0;x<REGION_SIZE;x++)
      if (game->getTerrainBit(tx+x,ty+y).isTree)
      	trees.push_back(new Tree(tx+x,(int)game->getTerrainBit(tx,ty).position->y,ty+y,parent));
}

/// Constructs the triangles
void Region::initialiseTriangles()
{
  clearTriangleData();
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(REGION_SIZE+1);y++)
		for (int x = 0; x<(REGION_SIZE+1);x++)
		{
      addPoint(Vector3(x,
			                 game->getTerrainBit(x+position.x,y+position.z).position->y,
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

/// Render this region and the trees
void Region::Render()
{
  Object::Render();
  for (unsigned int i = 0; i<trees.size();i++)
  	trees[i]->Render();
}

/// Returns the x coordinate
float Region::getOriginX()
{
  return position.x;
}
/// Returns the y coordinate (z in gamespace)
float Region::getOriginY()
{
  return position.z;
}
