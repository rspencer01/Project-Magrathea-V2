#include <stdio.h>
#include <glm.hpp>
#include <book.h>
#include <log.h>

//  The constructor...
/// @param g The function that the book should call in order to populate the data range
Book::Book(float (*g)(int,int))
{
  logi.log("Initialising book");
  generatingFunction = g;
  // Initialise all the pages to nothingness
  for (int i = 0;i<PAGE_COUNT;i++)
    for (int j = 0;j<PAGE_COUNT;j++)
      pages[i][j] = NULL;
  // No pages are initialised yet
  numberOfInitialisedPages = 0;
  // Initialise the null bit
  nullBit.position = glm::vec3(0.f);
  nullBit.normal = glm::vec3(0.f);
  nullBit.isTree = false;
  nullBit.isGrass = false;
  nullBit.isFern = false;
  // Initialise the deletion indices
  delI = delJ = 0;
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
    logi.log("Paging size: %lukB",(unsigned long)numberOfInitialisedPages*sizeof(Page)/1024);
  }
  // Ask the page for the terrainBit
  return pages[px][py]->getAt(x%PAGE_SIZE,y%PAGE_SIZE);
}

int Book::getNumberOfInitialisedPages()
{
  return numberOfInitialisedPages;
}

/// Delete pages that have marked themself as ready for removal.
void Book::deleteUnused()
{
  // delI and delJ are the indices that are updated each frame
  // Check if the page exists, and if so, if it wants to go
  if (pages[delI][delJ]!=NULL)
    if (pages[delI][delJ]->toBeDeleted())
    {
      // Free it up, then set it as empty
      delete pages[delI][delJ];
      pages[delI][delJ] = NULL;
      // Some feedback for the user
      numberOfInitialisedPages--;
      logi.log("Paging size: %lukB",(unsigned long)(numberOfInitialisedPages*sizeof(Page)/1024));
    }
  // Update the indices
  delI++;
  // Roll over
  if (delI>=PAGE_COUNT)
  {
    delI = 0;
    delJ++;
    if (delJ>=PAGE_COUNT)
      delJ = 0;
  }
}
