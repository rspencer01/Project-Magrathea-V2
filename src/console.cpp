#include <stdio.h>
#include <game.h>

void runConsole(Game* game)
{
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
      printf("(q)uit\n");
    }
    char option;
    scanf("%c",&option);
    if (option=='m')
      showMenu = !showMenu;
    if (option=='q')
      break;
    if (option=='v')
    {
      for (int y = 0;y<80;y++)
      {
        for (int x = 0;x<80;x++)
        {
          terrainBit here = game->getTerrainBit(x,y);
          if (here.isTree)
            printf("T");
          else
            printf(" ");
        }
        printf("\n");
      }
    }

  }
}
