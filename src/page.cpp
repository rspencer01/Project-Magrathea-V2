#include <stdio.h>
#include <page.h>
#include <noise.h>
#include <time.h>

Page::Page(int x,int y,float(*g)(int,int))
{
  printf("New page at %d %d\n",x,y);
  generatingFunction = g;
  origin_x = x;
  origin_y = y;
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
      data[i][j].position = new Vector3((float)origin_x+i,generatingFunction(origin_x+i,origin_y+j),(float)origin_y+j);
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
    {
      if ((i>0) && (j>0))
      {
        Vector3 a = *(data[i-1][j].position) - *(data[i][j].position);
        Vector3 b = *(data[i][j-1].position) - *(data[i][j].position);
        data[i][j].normal = new Vector3(b.cross(a).normal());
      }
      else
      {
        if ((origin_x+i>0) && (origin_y+j>0))
        {
          Vector3 a = Vector3((float)origin_x+i-1,generatingFunction(origin_x+i-1,origin_y+j),(float)origin_y+j) - *(data[i][j].position);
          Vector3 b = Vector3((float)origin_x+i,generatingFunction(origin_x+i,origin_y+j-1),(float)origin_y+j-1) - *(data[i][j].position);
          data[i][j].normal = new Vector3(b.cross(a).normal());

        }
        else
          data[i][j].normal = new Vector3(0,1,0);
      }
    }
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
    {
      data[i][j].type = grass;
      if (data[i][j].normal->y<0.6)
        data[i][j].type = stone;
    }
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
    {
      if (data[i][j].normal->y>0.75)
        data[i][j].isGrass = noise(origin_x-i,origin_y-j)<0.98;
      else
        data[i][j].isGrass = false;
      
      data[i][j].isTree = false;
      if (data[i][j].normal->y>0.9)
        if (noise(origin_x+i,origin_y+j)<0.01)
        {
          data[i][j].isTree = true;
          data[i][j].type = soil;
        }

      data[i][j].isFern = false;  
      if (data[i][j].normal->y>0.83)
        if ((!data[i][j].isTree) && noise(origin_x+i,origin_y+j)<0.15)
        {
          data[i][j].isFern = true;
          data[i][j].type = soil;
        }
    }
  // This is **very** buggy fixme soon please
  for (int i = 1;i<PAGE_SIZE-1;i++)
    for (int j = 1;j<PAGE_SIZE-1;j++)
    {
      if (data[i][j].isTree)
      for (int x = -1;x<2;x++)
        for (int y = -1;y<2;y++)
          data[i+x][j+y].type = soil;

    }

}

/// Returns the data at *internal coordinate* x,y
terrainBit Page::getAt(int x,int y)
{
  timeSinceLastAccess = time(NULL);
  return data[x][y];
}

bool Page::toBeDeleted()
{
  return (time(NULL)-timeSinceLastAccess)>PAGE_LIFE;
}