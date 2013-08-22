#include <stdio.h>
#include <GL/glut.h>

#include <gameops.h>
#include <graphics.h>
#include <heightmap.h>

// This is necessary so that we have a static funtion to call on display updates/keyboard etc.  We store the current game, and then functions wrap the actual code.
gameops* currentGame;
// A wrapper for displaying
void displayCurrentGame()
{
  currentGame->display();
}

/// The constructor for the gameops class
///
/// This function is called on the creation of a new game.  It loads
/// all the data, initialises the screen and keyboard functions.
gameops::gameops()
{
  printf("New game\n");
  initialiseHeightmap();
  initialiseGraphics();
  glutDisplayFunc(displayCurrentGame);
}

/// Run the game
void gameops::run()
{
  printf("Running game...\n");
}

/// Actually calls the functions to display stuff to the screen.
void gameops::display()
{
  glClearColor(1,0,0,1);
}
