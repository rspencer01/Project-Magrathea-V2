#include <stdio.h>
#include <book.h>

//  The constructor...
/// @param g The function that the book should call in order to populate the data range
Book::Book(float (*g)(int,int))
{
  printf("Initialising book\n");
  generatingFunction = g;
  for (int i = 0;i<PAGE_COUNT;i++)
    for (int j = 0;j<PAGE_COUNT;j++)
      pages[i][j] = NULL;
}

/// Frees up all used space
Book::~Book()
{
  for (int i = 0;i<PAGE_COUNT;i++)
    for (int j = 0;j<PAGE_COUNT;j++)
      if (pages[i][j])
        delete pages[i][j];
}

/// Actually does the accessing of the data
terrainBit Book::getAt(int x, int y)
{
  terrainBit nullBit;
  nullBit.position = new Vector3((float)x,0.f,(float)y);
  nullBit.normal = new Vector3(0.f,1.f,0.f);
  nullBit.isTree = false;
  // Check that this is a valid point to enquire about.  If not, return a nothing.
  if ((x > PAGE_COUNT * PAGE_SIZE) || (x<0))
    return nullBit;
  if ((y > PAGE_COUNT * PAGE_SIZE) || (y<0))
    return nullBit;
  // Get the page coordinates
  int px = x/PAGE_SIZE;
  int py = y/PAGE_SIZE;
  // If the page does not exist, create it.
  if (pages[px][py]==NULL)
    pages[px][py] = new Page(px*PAGE_SIZE,py*PAGE_SIZE,generatingFunction);
  // Ask the page for the terrainBit
  return pages[px][py]->getAt(x%PAGE_SIZE,y%PAGE_SIZE);
}
