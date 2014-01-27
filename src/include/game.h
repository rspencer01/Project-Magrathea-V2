/**
 * @file game.h
 * @author Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the game class, that handles keypresses and rendering.
 */

#ifndef GAMEOPS_H
#define GAMEOPS_H

#include <magrathea.h>

#include <camera.h>
#include <region.h>
#include <book.h>
#include <sky.h>
#include <queue>
#include <vector>
#include <testobj.h>
#include <shaders.h>
#include <shadow.h>
#include <bird.h>
#include <cloud.h>
#include <objectManager.h>
#include <water.h>

/// The gameops class contains all the methods to do with gameplay
///
/// This class interacts with glut graphics and keyboard handlers, and contains all the objects assiciated with a game instance.
/// It handles the render sequence (shadows) and all interactions with the user go through here.
class Game
{
  private:

    /// A list of regions in the game
    Region** regions[128];
    /// The book of all terrain data.
    Book* data;
    /// Passes all the required functions to glut
    void initialiseCallbacks();
    /// Resets all the keys
    void initialiseKeyops();
    /// Initialise the shaders and camera
    void initialisePipeline();
	  /// Sets the camera's vertical position, based on the terrain.
	  void setCameraFPS();
    /// A list of all keys that are currently depressed.
    bool keyDown [256];
    /// Called on each frame update.  Performs relevant operations, based on key positions.
    void keyOperations();
    /// Constructs regions in an area about the given point.
    void constructRegions(float,float);
    /// The camera speed
    float speed;
	  /// Are we in FPS mode?
	  bool fpsOn;
	  /// Are we showing the menu?
	  bool showMenu;
	  /// Function to show the menu
    // TODO : fixme, wrt shaders
	  void renderMenu();
    /// The shadow manager.  Handles all the shadow shader stuff
    ShadowManager* shadows;
    /// A test cloud
    Cloud* cloud;
    /// A test body of water
    Water* water;
    /// Is the mouse being used to control the camera
    bool mouseControl;
    /// Number of milliseconds since first frame
    int gameTime;
  public:
    /// Creates a game instance and initialises all variables.  If false is passed as a paramter, the game initialises no graphics
    Game(bool);
    /// Runs the game
    void run();
    /// Called each frame to show stuff on the screen
    void display();
    /// Event handler for a key press
    void keyPress(unsigned char key, int, int);
    /// Event handler for a key release
    void keyUp(unsigned char key, int, int);
    /// Event handler for the mouse move
    void mouseMove(int x, int y);
    /// Event handler for mouse events
    void mouse(int button, int state, int x, int y);
    /// Returns data about a single point
    terrainBit getTerrainBit(int x, int y);
    /// The shader that runs most of the rendering
    ShaderProgram* mainShader;
    /// Draws all the things in the world
    void RenderScene(int);
    /// The sky above our heads
    Sky* sky;
    /// The user camera that contains the fps position rotation etc.
    Camera* camera;
};

#endif
