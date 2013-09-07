#include <stdio.h>
#include <game.h>

char map[100][100];
Game* gam;

void printMap()
{
  printf("+");
  for (int i = 0;i<100;i++)
    printf("-");
  printf("+\n");
  for (int i = 0;i<100;i++)
  {
    printf("|");
    for (int j = 0;j<100;j++)
      printf("%c",map[i][j]);
    printf("|\n");
  }
  printf("+");
  for (int i = 0;i<100;i++)
    printf("-");
  printf("+\n");
}

void clearMap()
{
  for (int i = 0;i<100;i++)
    for (int j = 0;j<100;j++)
      map[i][j]=' ';
}

void doVeg()
{
  for (int y = 0;y<100;y++)
    for (int x = 0;x<100;x++)
    {
      terrainBit here = gam->getTerrainBit(x,y);
      if (here.isTree)
        map[y][x] = 'T';
    }
}

void doContour()
{
  for (int y = 1;y<100;y++)
  {
    for (int x = 1;x<100;x++)
    {
      bool isContour = false;
      if ((int)(gam->getTerrainBit(x,y).position->y/5) > (int)(gam->getTerrainBit(x-1,y).position->y/5))
        isContour = true;
      if ((int)(gam->getTerrainBit(x,y).position->y/5) > (int)(gam->getTerrainBit(x+1,y).position->y/5))
        isContour = true;
      if ((int)(gam->getTerrainBit(x,y).position->y/5) > (int)(gam->getTerrainBit(x,y-1).position->y/5))
        isContour = true;
      if ((int)(gam->getTerrainBit(x,y).position->y/5) > (int)(gam->getTerrainBit(x,y+1).position->y/5))
        isContour = true;
      if (isContour) 
        map[y][x] = '.';
    }
  }
}

void runConsole(Game* gme)
{
  gam = gme;
  printf("Entering console mode...\n");
  bool showMenu = true;
  while (1)
  {
    if (showMenu)
    {
      printf("Console menu\n");
      printf("------------\n");
      printf("Show/Hide (m)enu\n");
      printf("Display (v)egitation\n");
      printf("Display (c)ontours\n");
      printf("Display (t)opological (composite)\n");
      printf("(q)uit\n");
    }
    clearMap();
    char option = getchar();
    if (option=='m')
      showMenu = !showMenu;
    if (option=='q')
      break;
    if (option=='v')
      doVeg();
    if (option=='c')
      doContour();
    if (option=='t')
    {
      doContour();
      doVeg();
    }
    printMap();
    getchar();
  }
}
