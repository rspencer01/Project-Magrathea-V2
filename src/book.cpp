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
float Book::getAt(int x, int y)
{
  if ((x > PAGE_COUNT * PAGE_SIZE) || (x<0))
    return 0.f;
  if ((y > PAGE_COUNT * PAGE_SIZE) || (y<0))
    return 0.f;
  int px = x/PAGE_SIZE;
  int py = y/PAGE_SIZE;
  if (pages[px][py]==NULL)
    pages[px][py] = new Page(px*PAGE_SIZE,py*PAGE_SIZE,generatingFunction);
  return pages[px][py]->getAt(x%PAGE_SIZE,y%PAGE_SIZE);
}
