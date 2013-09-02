/**
 * @file game.h
 * @author Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the game class, that handles keypresses and rendering.
 */

#ifndef GAMEOPS_H
#define GAMEOPS_H

class Game;

#include <camera.h>
#include <region.h>
#include <book.h>
#include <sky.h>
#include <queue>
#include <testobj.h>
#include <shaders.h>

/// The gameops class contains all the methods to do with gameplay
///
/// This class interacts with glut graphics and keyboard handlers, and contains all the objects assiciated with a game instance.
class Game
{
  private:
    /// The user camera that contains the fps position rotation etc.
    Camera* camera;
    /// A list of regions in the game
    std::deque<std::deque<Region*> > regions;
    /// The sku above our heads
    Sky* sky;
    /// The book of all terrain data
    Book* data;
    /// Passes all the required functions to glut
    void initialiseCallbacks();
    /// Resets all the keys
    void initialiseKeyops();
	/// Sets the camera vertical position, based on the terrain
	void setCameraFPS();
    /// A list of all keys that are currently depressed
    bool keyDown [256];
    /// Called on each frame update.  Performs relevant operations, based on key positions
    void keyOperations();
    /// Constructs regions in an area about the given point.
    void constructRegions(float,float);
    /// The camera speed
    float speed;
	/// Are we in FPS mode?
	bool fpsOn;
	/// Are we showing the menu?
	bool showMenu;
	/// Do the menu
	void renderMenu();
    TestObj* test;
    ShaderProgram* mainShader;
  public:
    /// Creates a game instance and initialises all variables
    Game();
    /// Runs the game
    void run();
    /// Called each frame to show stuff on the screen
    void display();
    /// Event handler for a key press
    void keyPress(unsigned char key, int, int);
    /// Event handler for a key release
    void keyUp(unsigned char key, int, int);
    /// Returns data about a single point
    terrainBit getTerrainBit(int x, int y);
    /// The matrix by which the world should be tranformed (for this camera)
    float transMatrix[16];
};

#endif
