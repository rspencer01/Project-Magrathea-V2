#include <stdio.h>
#include <GL/glut.h>

#include <game.h>
#include <graphics.h>
#include <heightmap.h>

// This is necessary so that we have a static funtion to call on display updates/keyboard etc.  We store the current game, and then functions wrap the actual code.
Game* currentGame;
// A wrapper for displaying
void displayCurrentGame()
{
  currentGame->display();
}
void keyUpCurrentGame(unsigned char key,int x,int y)
{
  currentGame->keyUp(key,x,y);
}
void keyPressCurrentGame(unsigned char key,int x,int y)
{
  currentGame->keyPress(key,x,y);
}

/// The constructor for the gameops class
///
/// This function is called on the creation of a new game.  It loads
/// all the data, initialises the screen and keyboard functions.
Game::Game()
{
  printf("New game\n");
  initialiseHeightmap();
  initialiseGraphics();
  initialiseCallbacks();
  initialiseKeyops();
  currentGame = this;
  regions.push_back(Region(0,0,this));
  regions.push_back(Region(30,0,this));
  regions.push_back(Region(0,30,this));
}

/// This function assigns the event handlers defined at the top of this
/// file to their relevent events.
void Game::initialiseCallbacks()
{
  printf("Initialising callbacks\n");
  // The display function should be called whenever possible
  glutDisplayFunc(displayCurrentGame);
  glutIdleFunc(displayCurrentGame);
  // Resize
  glutReshapeFunc(resize);
  // Log the key functions
  glutKeyboardFunc(keyPressCurrentGame);
  glutKeyboardUpFunc(keyUpCurrentGame);
}

/// Run the game
void Game::run()
{
  printf("Running game...\n");
  glutMainLoop();
}

/// Actually calls the functions to display stuff to the screen.
void Game::display()
{
  // Do all the key stuff
  keyOperations();

  // Clear the display
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glClearColor(100,0,0,0.5);

  // Load a fresh matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Do the camera stuff
  camera.Render();

  // Render each region
  for (unsigned int i = 0;i<regions.size();i++)
	  regions[i].Render();

  // ..and blit it to the screen
  glutSwapBuffers();
}

void Game::initialiseKeyops()
{
  printf("Initialising keyops\n");
  for (int i = 0; i<=255; i++)
    keyDown[i] = false;
}

/// Handles the event of a key press, performing the required operations
void Game::keyPress(unsigned char key, int x, int y)
{
  keyDown[key] = true;
}

/// Handles the event of a key release
void Game::keyUp(unsigned char key, int x, int y)
{
  keyDown[key] = false;
}

/// Does all the things required per key
void Game::keyOperations()
{
  // Camera movement
  if (keyDown['w'])
    camera.MoveForward(0.1);
  if (keyDown['s'])
    camera.MoveForward(-0.1);
  if (keyDown['a'])
    camera.RotateFlat(0.05);
  if (keyDown['d'])
    camera.RotateFlat(-0.05);
  if (keyDown['q'])
    camera.RotateX(0.05);
  if (keyDown['e'])
    camera.RotateX(-0.05);
}

float Game::getTerrainBit(int x,int y)
{
  return getHeightmapData(x,y); 
}
