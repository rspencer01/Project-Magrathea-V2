#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

#include <game.h>
#include <graphics.h>
#include <heightmap.h>
#include <shaders.h>
#include <images.h>

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
  printf("New game\n");
  initialiseHeightmap();
  if (doGraphics)
  {
    initialiseGraphics(this);
    initialiseCallbacks();
    initialiseKeyops();
    initialisePipeline();
  }
  data = new Book(getHeightmapData);
  currentGame = this;
  speed = 0.1;
  fpsOn = true;
  showMenu = false;
  if (doGraphics)
  {
    sky = new Sky(this); 
    for (int i = 0; i<300;i++)
    {
      Vector3 t = randomVector()*100;
      t.y = 0;
      birds.push_back(new Bird(Vector3(100,60,100)+t,this));
    }
  }
}

/// Initialises all the shaders and cameras and shadows associated with this game
void Game::initialisePipeline()
{
  printf("Initialising pipeline\n");
  // Construct the main shader program
  mainShader = new ShaderProgram();
  // Load in our shaders
  mainShader->LoadShader("../shaders/vertexShader.shd", GL_VERTEX_SHADER);
  mainShader->LoadShader("../shaders/fragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile and load them
  mainShader->CompileAll();
  mainShader->Load();
  // Construct a new camera, linking to the transformationMatrix of the above shader
  camera = new Camera(mainShader,"transformationMatrix");
  // Put it somewhere nice to start with
  camera->Position = Vector3(5,1,5);
  camera->RotateY(-3.1415/2);
  // Initialise the shadows
  shadows = new ShadowManager();
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

/// Draws the entire game
void Game::RenderScene(int refreshTime)
{
  // Run through the rectangle of regions, and draw each one
  for (unsigned int i = 0;i<regions.size();i++)
    for (unsigned int j = 0;j<regions[i].size();j++)
      regions[i][j]->Render(refreshTime);
  for (unsigned int i = 0;i<birds.size();i++)
    birds[i]->Render(refreshTime);
}

int shadowsDone = 0;
/// Actually calls the functions to display stuff to the screen.
void Game::display()
{
  int refreshTime = getFrameTime();
  // log this frame in the framecount
  logFrame();
  // Do all the key stuff
  keyOperations();

  if (fpsOn)
    setCameraFPS();

  // Make whatever regions are required
  constructRegions(camera->Position.x,camera->Position.z);
  
  shadows->relocate(camera->Position,refreshTime);
  if (shadows->readyForWriting(refreshTime))
  {
    // Create the shadow texture
    RenderScene(0);
    shadows->readyForReading(mainShader);
  }
   
  // Render to the screen
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glClearColor(0.813,0.957,0.99,1);
  camera->Render();
  // Gogogo!
  sky->Render(refreshTime);
  RenderScene(refreshTime);
  
  // Push this to the screen
  glutSwapBuffers();

}

/// Create a first person scene with the camera
void Game::setCameraFPS()
{
  // Get the integer coordinates of the camera position
	float fx = camera->Position.x - (int)camera->Position.x;
	float fy = camera->Position.z - (int)camera->Position.z;
  // Now do the horrible interpolating to get the altitude of the camera
	camera->Position.y = interpolate(
						interpolate(getTerrainBit((int)camera->Position.x,(int)camera->Position.z).position->y,
									getTerrainBit((int)camera->Position.x+1,(int)camera->Position.z).position->y,
									fx),
						interpolate(getTerrainBit((int)camera->Position.x,(int)camera->Position.z+1).position->y,
									getTerrainBit((int)camera->Position.x+1,(int)camera->Position.z+1).position->y,
									fx),
						fy) + 0.63;
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

terrainBit Game::getTerrainBit(int x,int y)
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
		regions.push_back(std::deque<Region*>());
		Region* rg = new Region(rx,ry,this);
		regions[0].push_back(rg);
	}
  
	if (regions.back().back()->getOriginY() < ry+REGION_SIZE*7)
	{
		int oy = regions.back().back()->getOriginY();
		Region* rg = new Region(rx,oy+REGION_SIZE,this);
		regions.push_back(std::deque<Region*>());
		regions.back().push_back(rg);
	}
	if (regions.back().back()->getOriginY() > ry+REGION_SIZE*7)
	{
		for (unsigned int i = 0; i <regions.back().size();i++)
			delete regions.back()[i];
		regions.pop_back();
	}

	if (regions.front().back()->getOriginY() > ry-REGION_SIZE*7)
	{
    int oy = regions.front().back()->getOriginY();
    if (oy-REGION_SIZE>=0)
    {
		  Region* rg = new Region(rx,oy-REGION_SIZE,this);
		  regions.push_front(std::deque<Region*>());
		  regions.front().push_back(rg);
    }
	}
	if (regions.front().back()->getOriginY() < ry-REGION_SIZE*7)
	{
		for (unsigned int i = 0; i <regions.front().size();i++)
			delete regions.front()[i];
		regions.pop_front();
	}

	
	for (unsigned int i = 0;i<regions.size();i++)
	{
		if (regions[i].back()->getOriginX() < rx+REGION_SIZE*7)
			regions[i].push_back(new Region(regions[i].back()->getOriginX()+REGION_SIZE,regions[i].back()->getOriginY(),this));
		if (regions[i].back()->getOriginX() > rx+REGION_SIZE*7)
		{
			delete regions[i].back();
			regions[i].pop_back();
		}
		if (regions[i].front()->getOriginX() > rx-REGION_SIZE*7)
      if (regions[i].front()->getOriginX()-REGION_SIZE>=0)
			  regions[i].push_front(new Region(regions[i].front()->getOriginX()-REGION_SIZE,regions[i].front()->getOriginY(),this));
		if (regions[i].front()->getOriginX() < rx-REGION_SIZE*7)
		{
			delete regions[i].front();
			regions[i].pop_front();
		}
	}
	
  
}

void Game::renderMenu()
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glColor4f(0,0,0,0.85);
  glTranslatef(camera->Position.x,camera->Position.y,camera->Position.z);
  glutSolidSphere(0.25,10,10);
  writeString(3,95,"PROJECT MAGRATHEA V2");
  writeString(3,91, "====================");
  writeString(3,87,"Controls:");
  writeString(3,83,"  <m> Toggle menu");
  writeString(3,79,"  <o> Toggle first person");
  writeString(3,75,"  <x> Speed up");
  writeString(3,71,"  <z> Slow down");
}

void Game::setProjectionMatrix(float* mat)
{
  mainShader->setMatrix("projectionMatrix",mat);
}
