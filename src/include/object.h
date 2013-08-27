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
#include <vector>

/// An object is anything that occurs in the game space
class Object
{
  private:
  protected:
    /// Two vectors to hold the triangle and position data while we collect them
	  std::vector<int> triDat;
  	std::vector<float> posDat;
    /// Where is this thing?
    Vector3 position;
    Game* game;
  	/// Vertex buffer for the position of each vertex
    GLuint vertexVBO;
    /// Vertex buffer for the indexes of each triangle
    GLuint indexVBO;
    /// Have these things been initialised (can I destroy them?)
    bool buffersInitialised;
    /// How many triangles in this thing?
    int numberOfTriangles;
    /// Initialise the triangle and position datas
    void clearTriangleData(int,int);
    /// Adds a new vertex to the shape of this thing
    void addPoint(int,Vector3);
    /// Constructs a triangle with given points
  	void addTriangle(int,int,int,int);
    /// Pushes the triangle data to the graphics card
	  void pushTriangleData();
  public:
	  /// Constructs the object with the given coordinates and in the given game
    Object(Vector3,Game*);
  	/// Destroys the Object, freeing space
    ~Object();
  	/// Renders the Object to the screen
    void Render();
  	/// Accessor for the item position
    Vector3 getPosition();
};


#endif
