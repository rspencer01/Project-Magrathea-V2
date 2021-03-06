#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <gtx/random.hpp>

#include <game.h>
#include <graphics.h>
#include <heightmap.h>
#include <shaders.h>
#include <images.h>
#include <cmath>

#include <fpscounter.h>
// This is necessary so that we have a static funtion to call on display updates/keyboard etc.  
// We store the current game, and then functions wrap the actual code.
Game* currentGame;
// A static wrapper for displaying
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
void mouseMoveCurrentGame(int x,int y)
{
  currentGame->mouseMove(x,y);
}
void mouseCurrentGame(int button, int state, int x,int y)
{
  currentGame->mouse(button,state,x,y);
}



// TODO Move this somewhere better
inline float interpolate(float a, float b, float t)
{
	return a*(1-t) + b*t;
}


/// The constructor for the gameops class
///
/// This function is called on the creation of a new game.  It loads
/// all the data, initialises the screen and keyboard functions.
/// @param doGraphics Should this game initialise graphics?
Game::Game(bool doGraphics)
{
  logi.log("New game");
  initialiseHeightmap();
  if (doGraphics)
  {
    initialiseGraphics(this);
    initialiseCallbacks();
    initialiseKeyops();
    initialisePipeline();
  }
  data = new Book(getHeightmapData);
  grassManager = new GrassManager(this);
  currentGame = this;
  speed = 0.1f;
  fpsOn = false;
  showMenu = false;
  if (doGraphics)
  {
    sky = new Sky(this); 
  }
  cloud = new Cloud(glm::vec3(0,500,0),this);
  water = new Water(glm::vec3(0,8,0),this);
  for (unsigned int i = 0;i<128;i++)
  {
    regions[i] = new Region* [128];
    for (unsigned int j = 0;j<128;j++)
      regions[i][j] = NULL;
  }
  gameTime = 0;
}

/// Initialises all the shaders and cameras and shadows associated with this game
void Game::initialisePipeline()
{
  logi.log("Initialising pipeline");
  // Construct the main shader program
  mainShader = new ShaderProgram();
  // Load in our shaders
  mainShader->LoadShader("../shaders/vertexShader.shd", GL_VERTEX_SHADER);
  mainShader->LoadShader("../shaders/fragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile and load them
  mainShader->CompileAll();
  mainShader->Load();
  // Construct a new camera, linking to the transformationMatrix of the above shader
  camera = new Camera(&mainShader->frameData.cameraMatrix,&mainShader->frameData.cameraPos);
  // Put it somewhere nice to start with
  camera->setPosition(glm::vec3(5,100,5));
  camera->RotateY(-3.1415f/2.f);
  // Initialise the shadows
  shadows = new ShadowManager(mainShader);

  mouseControl = true;
}

/// This function assigns the event handlers defined at the top of this
/// file to their relevent events.
void Game::initialiseCallbacks()
{
  logi.log("Initialising callbacks");
  // The display function should be called whenever possible
  glutDisplayFunc(displayCurrentGame);
  glutIdleFunc(displayCurrentGame);
  // Resize
  glutReshapeFunc(resize);
  // Log the key functions
  glutKeyboardFunc(keyPressCurrentGame);
  glutKeyboardUpFunc(keyUpCurrentGame);
  glutPassiveMotionFunc(mouseMoveCurrentGame);
  glutMouseFunc(mouseCurrentGame);
}

/// Run the game
void Game::run()
{
  logi.log("Running game...");
  glutMainLoop();
}

/// Draws the entire game
void Game::RenderScene(int refreshTime)
{
  // Run through the rectangle of regions, and draw each one
  for (unsigned int i = 0;i<128;i++)
    for (unsigned int j = 0;j<128;j++)
      if (regions[i][j]!=NULL)
        regions[i][j]->Render(refreshTime,camera->getPosition());
  grassManager->Render(refreshTime,camera->getPosition());
}

/// Actually calls the functions to display stuff to the screen.
void Game::display()
{
  int refreshTime = getFrameTime();
  mainShader->frameData.gameTime = gameTime;
  gameTime += refreshTime;
  // log this frame in the framecount
  logFrame();
  // Do all the key stuff
  keyOperations();

  // Lock the player to the ground if required
  if (fpsOn)
    setCameraFPS();
  
  // Make whatever regions are required
  constructRegions(camera->getPosition().x,camera->getPosition().z);
  // Destroy unused pages
  data->deleteUnused();
  
  // Do the shadow stuff
  shadows->relocate(camera->getPosition(),refreshTime);

  shadows->readyForWriting(refreshTime);
  // Create the shadow texture
  RenderScene(0);
  
  // And reset
  shadows->readyForReading(mainShader);
  
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //glClearColor((GLclampf)0.813,(GLclampf)0.957,(GLclampf)0.99,(GLclampf)1.0);
  glClearColor((GLclampf)1,(GLclampf)1.0,(GLclampf)1.0,(GLclampf)1.0);
  
  camera->Render();
  mainShader->setFrameData();
  
  // Gogogo!
  sky->Render(refreshTime,camera->getPosition());
  water->Render(refreshTime,camera->getPosition());
  //cloud->Render(refreshTime,&(camera->Position));
  RenderScene(refreshTime);
  
  
  // Push this to the screen
  glutSwapBuffers();
}

/// Create a first person scene with the camera
void Game::setCameraFPS()
{
  // Get the integer coordinates of the camera position
	float fx = camera->getPosition().x - (int)camera->getPosition().x;
	float fy = camera->getPosition().z - (int)camera->getPosition().z;
  // Now do the horrible interpolating to get the altitude of the camera
	camera->setPosition(
    glm::vec3(camera->getPosition().x,
             interpolate(
						interpolate(getTerrainBit((int)camera->getPosition().x,(int)camera->getPosition().z).position.y,
									getTerrainBit((int)camera->getPosition().x+1,(int)camera->getPosition().z).position.y,
									fx),
						interpolate(getTerrainBit((int)camera->getPosition().x,(int)camera->getPosition().z+1).position.y,
									getTerrainBit((int)camera->getPosition().x+1,(int)camera->getPosition().z+1).position.y,
									fx),
						fy) + 1.63f,
            camera->getPosition().z));
}

void Game::initialiseKeyops()
{
  logi.log("Initialising keyops");
  for (int i = 0; i<=255; i++)
    keyDown[i] = false;
}

/// Handles the event of a key press, performing the required operations
void Game::keyPress(unsigned char key, int x, int y)
{
  keyDown[key] = true;
  if (key=='x')
    speed *=2;
  if (key=='z')
    speed/=2;
  if (key=='o')
    fpsOn = !fpsOn;
  if (key=='m')
	showMenu = !showMenu;
}

/// Handles the event of a key release
void Game::keyUp(unsigned char key, int x, int y)
{
  keyDown[key] = false;
}

/// Does all the things required per key
void Game::keyOperations()
{
  // Camera movement (if playing
  if (!showMenu)
  {
	  if (keyDown['w'])
		  camera->MoveForward(speed);
	  if (keyDown['s'])
		camera->MoveForward(-speed);
  }
  if (keyDown['a'])
    camera->RotateFlat(0.01f);
  if (keyDown['d'])
    camera->RotateFlat(-0.01f);
  if (keyDown['q'])
    camera->RotateX(0.01f);
  if (keyDown['e'])
    camera->RotateX(-0.01f);
}

void Game::mouseMove(int x, int y)
{
  if (mouseControl)
  {
    // Get the centre of the screen
    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    // If the mouse has moved
    if (x!=centerX || y!=centerY)
    {
      // Rotate the camera
      camera->RotateFlat(-(x-centerX)/200.f);
      camera->RotateX(-(y-centerY)/200.f);
      // Grab that mouse again
      glutWarpPointer(centerX,centerY);
    }
  }
}


int lastLeftState = GLUT_UP;
int lastMiddleState = GLUT_UP;
void Game::mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    mouseControl ^= lastLeftState==GLUT_UP;
    lastLeftState = state;
  }
  if (mouseControl)
  {
    // Make there be no cursor
    glutSetCursor(GLUT_CURSOR_NONE);
    // Move the mouse to the centre screen
    int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
    glutWarpPointer(centerX,centerY);
  }
  else
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
  // Turn on the fps if required
  if (button == GLUT_MIDDLE_BUTTON)
  {
    fpsOn^=lastMiddleState==GLUT_UP;
    lastMiddleState = state;
  }

}


terrainBit Game::getTerrainBit(int x,int y)
{
  return data->getAt(x,y);
}

/// Constructs regions in an area around the given coordinates.  Does at most one region construction/destruction per call.
void Game::constructRegions(float x,float y)
{
  int numRegions = 5;
  int rx = (int)(x /REGION_SIZE);
  int ry = (int)(y /REGION_SIZE);
  for (int x = std::max(0,rx-numRegions);x<std::min(127,rx+numRegions);x++)
    for (int y = std::max(0,ry-numRegions);y<std::min(127,ry+numRegions);y++)
      if (regions[y][x] == NULL)
      {
        regions[y][x] = new Region(glm::vec3(x*REGION_SIZE,0,y*REGION_SIZE),this);
        return;
      }
}

void Game::renderMenu()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glColor4f(0,0,0,0.85f);
  //glTranslatef(camera->getPosition().x,camera->Position.y,camera->Position.z);
  glutSolidSphere(0.25,10,10);
  writeString(3,95,"PROJECT MAGRATHEA V2");
  writeString(3,91, "====================");
  writeString(3,87,"Controls:");
  writeString(3,83,"  <m> Toggle menu");
  writeString(3,79,"  <o> Toggle first person");
  writeString(3,75,"  <x> Speed up");
  writeString(3,71,"  <z> Slow down");
}