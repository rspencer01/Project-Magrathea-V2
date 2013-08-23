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
