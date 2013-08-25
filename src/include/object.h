/**
 * @file heightmap.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes objects
 */

#ifndef OBJECT_H
#define OBJECT_H

class Game;
#include <vector3.h>
#include <GL/glut.h>


/// An object is anything that occurs in the game space
class Object
{
  protected:
    /// Where is this thing?
    Vector3 position;
    Game* game;
  	/// Vertex buffer for the position of each vertex
	  GLuint vertexVBO;
	/// Vertex buffer for the indexes of each triangle
	  GLuint indexVBO;
  /// Have these things been initialised (can I destroy them?)
    bool buffersInitialised;
  public:
	/// Constructs the object with the given coordinates and in the given game
    Object(Vector3,Game*);
	/// Destroys the Object, freeing space
    ~Object();
	/// Renders the Object to the screen
    //void Render();
    Vector3 getPosition();
};


#endif
