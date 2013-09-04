#include <stdio.h>
#include <gl/glew.h>
#include <GL/glut.h>

#include <game.h>
#include <graphics.h>
#include <heightmap.h>
#include <shaders.h>
#include <images.h>

#include <fpscounter.h>
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

// TODO Move this somewhere better
inline float interpolate(float a, float b, float t)
{
	return a*(1-t) + b*t;
}


/// The constructor for the gameops class
///
/// This function is called on the creation of a new game.  It loads
/// all the data, initialises the screen and keyboard functions.
Game::Game()
{
  printf("New game\n");
  initialiseHeightmap();
  initialiseGraphics(this);
  initialiseCallbacks();
  initialiseKeyops();
  data = new Book(getHeightmapData);
  currentGame = this;
  speed = 0.1;
  fpsOn = true;
  showMenu = false;
  sky = new Sky(this);
  mainShader = new ShaderProgram();
  // Now load the two shaders
  mainShader->LoadShader("../shaders/vertexShader.shd", GL_VERTEX_SHADER);
  mainShader->LoadShader("../shaders/fragmentShader.shd", GL_FRAGMENT_SHADER);
  // Compile...
  mainShader->CompileAll();
  // And load
  mainShader->Load();

  // And load
  //shadowShader->Load();
  
  //shadowShader->setInt("gSampler",0);
  camera = new Camera(mainShader,"transformationMatrix");
  camera->Position = Vector3(5,1,5);
  camera->RotateY(-3.1415/2);
  test = new TestObj(this); 
  mainShader->Load();
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

void Game::RenderScene()
{
  for (unsigned int i = 0;i<regions.size();i++)
    for (unsigned int j = 0;j<regions[i].size();j++)
      regions[i][j]->Render();
}
  
/// Actually calls the functions to display stuff to the screen.
void Game::display()
{
  // Do all the key stuff
  keyOperations();

  if (fpsOn)
    setCameraFPS();

  // Make whatever regions are required
  constructRegions(camera->Position.x,camera->Position.z);
  
  // Create the shadow texture
  shadows->readyForWriting();
  RenderScene();
   
  // Render to the screen
  glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0,0.0,0.0,1);
  // Prepare the shadow texture
  mainShader->Load();
  shadows->readyForReading(mainShader);
  resize(500,500);
  mainShader->setInt("shadowTexture",7);
  mainShader->setInt("otherTexture",3);
  camera->Render();
  // Gogogo!
  RenderScene();
  

  glutSwapBuffers();

  // log this frame in the framecount
  logFrame();
}

void Game::setCameraFPS()
{
	float fx = camera->Position.x - (int)camera->Position.x;
	float fy = camera->Position.z - (int)camera->Position.z;
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
  
	if (regions.back().back()->getOriginY() < ry+REGION_SIZE*3)
	{
		int oy = regions.back().back()->getOriginY();
		Region* rg = new Region(rx,oy+REGION_SIZE,this);
		regions.push_back(std::deque<Region*>());
		regions.back().push_back(rg);
	}
	if (regions.back().back()->getOriginY() > ry+REGION_SIZE*3)
	{
		for (unsigned int i = 0; i <regions.back().size();i++)
			delete regions.back()[i];
		regions.pop_back();
	}

	if (regions.front().back()->getOriginY() > ry-REGION_SIZE*3)
	{
    int oy = regions.front().back()->getOriginY();
    if (oy-REGION_SIZE>=0)
    {
		  Region* rg = new Region(rx,oy-REGION_SIZE,this);
		  regions.push_front(std::deque<Region*>());
		  regions.front().push_back(rg);
    }
	}
	if (regions.front().back()->getOriginY() < ry-REGION_SIZE*3)
	{
		for (unsigned int i = 0; i <regions.front().size();i++)
			delete regions.front()[i];
		regions.pop_front();
	}

	
	for (unsigned int i = 0;i<regions.size();i++)
	{
		if (regions[i].back()->getOriginX() < rx+REGION_SIZE*3)
			regions[i].push_back(new Region(regions[i].back()->getOriginX()+REGION_SIZE,regions[i].back()->getOriginY(),this));
		if (regions[i].back()->getOriginX() > rx+REGION_SIZE*3)
		{
			delete regions[i].back();
			regions[i].pop_back();
		}
		if (regions[i].front()->getOriginX() > rx-REGION_SIZE*3)
      if (regions[i].front()->getOriginX()-REGION_SIZE>=0)
			  regions[i].push_front(new Region(regions[i].front()->getOriginX()-REGION_SIZE,regions[i].front()->getOriginY(),this));
		if (regions[i].front()->getOriginX() < rx-REGION_SIZE*3)
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
