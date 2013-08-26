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
    {
      data[i][j].position = new Vector3(origin_x+i,generatingFunction(origin_x+i,origin_y+j),origin_y+j);
      data[i][j].isTree = noise(x+i,y+j)<0.02;
    }
}

/// Returns the data at *internal coordinate* x,y
terrainBit Page::getAt(int x,int y)
{
  return data[x][y];
}
