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
  data = new Book(getHeightmapData);
  currentGame = this;
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

  // Make whatever regions are required
  constructRegions(camera.Position.x,camera.Position.z);

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
	  for (unsigned int j = 0;j<regions[i].size();j++)
		regions[i][j].Render();

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
    camera.MoveForward(0.1f);
  if (keyDown['s'])
    camera.MoveForward(-0.1f);
  if (keyDown['a'])
    camera.RotateFlat(0.05f);
  if (keyDown['d'])
    camera.RotateFlat(-0.05f);
  if (keyDown['q'])
    camera.RotateX(0.05f);
  if (keyDown['e'])
    camera.RotateX(-0.05f);
}

float Game::getTerrainBit(int x,int y)
{
  return data->getAt(x,y);
}

/// Constructs regions in an area around the given coordinates.  Does at most one region construction/destruction per call.
void Game::constructRegions(float x,float y)
{
	int rx = (int)(x /REGION_SIZE)*REGION_SIZE;
	int ry = (int)(y /REGION_SIZE)*REGION_SIZE;
	if (regions.size()==0)
	{
		regions.push_back(std::deque<Region>());
		regions[0].push_back(Region(rx,ry,this));
	}

	if (regions.back().back().getOriginY() < ry+REGION_SIZE)
	{
		int oy = regions.back().back().getOriginY();
		regions.push_back(std::deque<Region>());
		regions.back().push_back(Region(rx,oy+REGION_SIZE,this));
	}
	if (regions.back().back().getOriginY() > ry+REGION_SIZE)
		regions.pop_back();

	if (regions.front().back().getOriginY() > ry-REGION_SIZE)
	{
		int oy = regions.front().back().getOriginY();
		regions.push_front(std::deque<Region>());
		regions.front().push_back(Region(rx,oy-REGION_SIZE,this));
	}
	if (regions.front().back().getOriginY() < ry-REGION_SIZE)
		regions.pop_front();


	for (int i = 0;i<regions.size();i++)
	{
		if (regions[i].back().getOriginX() < rx+REGION_SIZE)
			regions[i].push_back(Region(regions[i].back().getOriginX()+REGION_SIZE,regions[i].back().getOriginY(),this));
		if (regions[i].back().getOriginX() > rx+REGION_SIZE)
			regions[i].pop_back();
		if (regions[i].front().getOriginX() > rx-REGION_SIZE)
			regions[i].push_front(Region(regions[i].front().getOriginX()-REGION_SIZE,regions[i].front().getOriginY(),this));
		if (regions[i].front().getOriginX() < rx-REGION_SIZE)
			regions[i].pop_front();
	}


}