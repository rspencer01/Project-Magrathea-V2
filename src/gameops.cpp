#include <stdio.h>

#include <gameops.h>
#include <graphics.h>

/// The constructor for the gameops class
///
/// This function is called on the creation of a new game.  It loads
/// all the data, initialises the screen and keyboard functions.
gameops::gameops()
{
  printf("New game\n");
  initialiseGraphics();
}
