#include <stdio.h>
#include <page.h>
#include <noise.h>

Page::Page(int x,int y,float(*g)(int,int))
{
  printf("New page at %d %d\n",x,y);
  generatingFunction = g;
  origin_x = x;
  origin_y = y;
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
      data[i][j].position = new Vector3(origin_x+i,generatingFunction(origin_x+i,origin_y+j),origin_y+j);
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
          Vector3 a = Vector3(i-1,generatingFunction(origin_x+i-1,origin_y+j),j) - *(data[i][j].position);
          Vector3 b = Vector3(i,generatingFunction(origin_x+i,origin_y+j-1),j-1) - *(data[i][j].position);
          data[i][j].normal = new Vector3(b.cross(a).normal());

        }
        else
          data[i][j].normal = new Vector3(0,1,0);
      }
    }
  for (int i = 0;i<PAGE_SIZE;i++)
    for (int j = 0;j<PAGE_SIZE;j++)
    {
      if (data[i][j].normal->y>0.85)
        data[i][j].isGrass = noise(origin_x-i,origin_y-j)<0.10;
      else
        data[i][j].isGrass = false;
      if (data[i][j].normal->y>0.9)
        data[i][j].isTree = !data[i][j].isGrass && noise(origin_x+i,origin_y+j)<0.05;
      else
        data[i][j].isTree = false;
    }
}

/// Returns the data at *internal coordinate* x,y
terrainBit Page::getAt(int x,int y)
{
  return data[x][y];
}
