#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <region.h>
#include <game.h>
#include <dynotree.h>
#include <grass.h>
#include <images.h>

GLuint texture = (GLuint)-1;

/// Constructs a new region at the given position
/// @param x The x coordinate of the origin
/// @param y The y coordinate of the origin
/// @param parent The game that this region is in.
Region::Region(int x, int y,Game* parent) : Object(Vector3(x,0.f,y),parent)
{
	printf("New region at %d %d\n",x,y);
	initialiseTriangles();
  for (int ty = 0;ty<REGION_SIZE;ty++)
    for (int tx = 0;tx<REGION_SIZE;tx++)
    {
      terrainBit here = game->getTerrainBit(tx+x,ty+y);
      if (here.isTree)
      {
        foliage.push_back(new DynoTree(*(here.position),parent));
      }
      if (here.isGrass)
        foliage.push_back(new Grass(*(here.position),*(here.normal),parent));
    }
  if (texture == (GLuint)-1)
	  texture = textureFromBMP("../assets/BigGrass.bmp");
  textureNumber = texture;
}

/// Constructs the triangles
void Region::initialiseTriangles()
{
  clearTriangleData((REGION_SIZE+1)*(REGION_SIZE+1),REGION_SIZE*REGION_SIZE*2);
	// There are (size+1)^2 vertices.  Bring in the data
	for (int y = 0; y<(REGION_SIZE+1);y++)
		for (int x = 0; x<(REGION_SIZE+1);x++)
		{
      addPoint(y*(REGION_SIZE+1)+x,
               Vector3(x,
			                 game->getTerrainBit(x+position.x,y+position.z).position->y,
			                 y),
                       *(game->getTerrainBit(x+position.x,y+position.z).normal),
                       0.41,0.61,0.24);
      editTextureCoord(y*(REGION_SIZE+1)+x,2.0*x/(REGION_SIZE+1),2.0*y/(REGION_SIZE+1));
		}
	
  // Populate one triangle (for now) per block
	for (int y = 0; y<REGION_SIZE;y++)
		for (int x = 0; x<REGION_SIZE;x++)
		{
      addTriangle((y*REGION_SIZE+x)*2,
                  y*(REGION_SIZE+1) + x,
			            (y+1)*(REGION_SIZE+1) + x,
			            y*(REGION_SIZE+1) + (x+1));
      addTriangle((y*REGION_SIZE+x)*2+1,
                  y*(REGION_SIZE+1) + x+1,
			            (y+1)*(REGION_SIZE+1) + x,
			            (y+1)*(REGION_SIZE+1) + (x+1));
		}
  pushTriangleData();
}

/// Render this region and the trees
void Region::Render()
{
  Object::Render();
  for (unsigned int i = 0; i<foliage.size();i++)
    foliage[i]->Render();
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
