#include <stdio.h>
#include <magrathea.h>
#include <region.h>
#include <game.h>
#include <dynotree.h>
#include <grass.h>
#include <images.h>
#include <smallFern.h>

GLuint texture = (GLuint)-1;

/// Constructs a new region at the given position
/// @param x The x coordinate of the origin
/// @param y The y coordinate of the origin
/// @param parent The game that this region is in.
Region::Region(int x, int y,Game* parent) : Object(Vector3((float)x,0.f,(float)y),parent)
{
	printf("New region at %d %d\n",x,y);
	initialiseTriangles();
  for (int ty = 0;ty<REGION_SIZE;ty++)
    for (int tx = 0;tx<REGION_SIZE;tx++)
    {
      terrainBit here = game->getTerrainBit(tx+x,ty+y);
      if (here.isTree)
      	foliage.push_back(new DynoTree(*(here.position),parent));
      //if (here.isGrass)
      //  foliage.push_back(new Grass(*(here.position),*(here.normal),parent));
      if (here.isFern)
        foliage.push_back(new SmallFern(*(here.position),*(here.normal),parent));
    }

  if (texture == (GLuint)-1)
	  texture = textureFromTGA("../assets/MixedGround.tga",true);
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
               Vector3((float)x,
			                 game->getTerrainBit(x+(int)position.x,y+(int)position.z).position->y,
			                 (float)y),
                       *(game->getTerrainBit(x+(int)position.x,y+(int)position.z).normal),
                       1,1,1);
      editTextureCoord(y*(REGION_SIZE+1)+x,4.f*x/(REGION_SIZE+1),4.f*y/(REGION_SIZE+1));
      terrainType t = game->getTerrainBit(x+(int)position.x,y+(int)position.z).type;
      if (t==grass)
        setTextureMix(y*(REGION_SIZE+1)+x,0,0,0,1);
      if (t==stone)
        setTextureMix(y*(REGION_SIZE+1)+x,0,1,0,0);
      if (t==sand)
        setTextureMix(y*(REGION_SIZE+1)+x,1,0,0,0);
      if (t==soil)
        setTextureMix(y*(REGION_SIZE+1)+x,0,0,1,0);

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
void Region::Render(int refreshTime)
{
  Object::Render(refreshTime);
  for (unsigned int i = 0; i<foliage.size();i++)
    foliage[i]->Render(refreshTime);
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
