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


/// An object is anything that occurs in the game space
class Object
{
  protected:
    /// Where is this thing?
	int origin_x;
	int origin_y;
	int origin_z;
	Game* game;
	/// Vertex buffer for the position of each vertex
	//GLuint vertexVBO;
	/// Vertex buffer for the indexes of each triangle
	//GLuint indexVBO;
  public:
	/// Constructs the object with the given coordinates and in the given game
    Object(int,int,int,Game*);
	/// Destroys the Object, freeing space
    ~Object();
	/// Renders the Object to the screen
    //void Render();
};


#endif
