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

typedef struct
{
  float px,py,pz;
  float red,green,blue,alpha;
  float nx,ny,nz;
  
  float texx,texy;
}/* __attribute__((packed)) */ VertexDatum;

/// An object is anything that occurs in the game space
class Object
{
  private:
  protected:
    /// Two arrays to hold the triangle and position data
	  int* triDat;
  	VertexDatum* vertexData;
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
    int numberOfPoints;
    /// Initialise the triangle and position datas
    void clearTriangleData(int,int);
    /// Adds a new vertex to the shape of this thing
    void addPoint(int,Vector3,Vector3,float,float,float);
    /// Constructs a triangle with given points
  	void addTriangle(int,int,int,int);
    /// Pushes the triangle data to the graphics card
	void pushTriangleData();
	/// Texture number.  -1 if there is no texture
	GLuint textureNumber;
	/// Setting uv coordinates
	void editTextureCoord(int, float, float);
	/// Repushes the vertexes to the GPU
    void updateTriangleData();
	/// Loads the object from an .obj file
	void loadFromOBJFile(const char*);
  public:
	  /// Constructs the object with the given coordinates and in the given game
    Object(Vector3,Game*);
  	/// Destroys the Object, freeing space
    ~Object();
  	/// Renders the Object to the screen
    void Render();
  	/// Accessor for the item position
    Vector3 getPosition();
    void setPosition(Vector3);
};


#endif
