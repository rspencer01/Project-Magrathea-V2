#include <stdio.h>
#include <book.h>

//  The constructor...
/// @param g The function that the book should call in order to populate the data range
Book::Book(float (*g)(int,int))
{
  printf("Initialising book\n");
  generatingFunction = g;
  // Initialise all the pages to nothingness
  for (int i = 0;i<PAGE_COUNT;i++)
    for (int j = 0;j<PAGE_COUNT;j++)
      pages[i][j] = NULL;
  // No pages are initialised yet
  numberOfInitialisedPages = 0;
}

/// Frees up all used space
Book::~Book()
{
  // Destroy all pages
  for (int i = 0;i<PAGE_COUNT;i++)
    for (int j = 0;j<PAGE_COUNT;j++)
      // We should first check that the page exists before destroying it.
      if (pages[i][j])
        delete pages[i][j];
}

/// Actually does the accessing of the data.  If the data does not exist (the coordinates are outside of the range)
/// then it returns a null bit (no vegitation, flat)
/// @param x The x coordinate to access
/// @param y The y coordinate to access
terrainBit Book::getAt(int x, int y)
{
  // The nullBit is used for areas that are not in the terrain
  terrainBit nullBit;
  nullBit.position = new Vector3((float)x,0.f,(float)y);
  nullBit.normal = new Vector3(0.f,1.f,0.f);
  nullBit.isTree = false;
  nullBit.isGrass = false;
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
  {
    pages[px][py] = new Page(px*PAGE_SIZE,py*PAGE_SIZE,generatingFunction);
    numberOfInitialisedPages++;
  }
  // Ask the page for the terrainBit
  return pages[px][py]->getAt(x%PAGE_SIZE,y%PAGE_SIZE);
}

int Book::getNumberOfInitialisedPages()
{
  return numberOfInitialisedPages;
}