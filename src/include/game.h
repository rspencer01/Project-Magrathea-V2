/**
 * @file game.h
 * @author Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the game class, that handles keypresses and rendering.
 */

#ifndef GAMEOPS_H
#define GAMEOPS_H

#include <camera.h>
#include <region.h>

/// The gameops class contains all the methods to do with gameplay
///
/// This class interacts with glut graphics and keyboard handlers, and contains all the objects assiciated with a game instance.
class Game
{
  private:
    /// Passes all the required functions to glut
    void initialiseCallbacks();
    /// A list of all keys that are currently depressed
    bool keyDown [256];
    /// Called on each frame update.  Performs relevant operations, based on key positions
    void keyOperations();
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
};

#endif
