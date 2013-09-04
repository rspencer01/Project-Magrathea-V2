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

#include <gl\glew.h>
#include <gl\glut.h>
#include <vector3.h>

/// \brief Contains all the information passed to the shaders.
///
/// This is passed to the vertex shader via four (currently) vertex attributes, one for each major attribute.
/// Soon it will be defined in the shader and then it will just be passed as flat data through one.
/// TODO Pass this in one data stream for GLSL portability
typedef struct
{
  /// The x component of the position of the vertex
  float px;
  /// The y component of the position of the vertex
  float py;
  /// The z component of the position of the vertex
  float pz;
  /// The red component of the vertex colour
  float red;
  /// The green component of the vertex colour
  float green;
  /// The blue component of the vertex colour
  float blue;
  /// The alpha component of the vertex colour
  float alpha;
  /// The x component of the normal at the vertex
  float nx;
  /// The y component of the normal at the vertex
  float ny;
  /// The z component of the normal at the vertex
  float nz;
  /// The x coordinates of the vertex texture
  float texx;
  /// The y coordinates of the vertex texture
  float texy;
} VertexDatum;

/// \brief An object is anything that occurs in the game space
///
/// This base class contains methods for constructing and rendering an object.
/// Rendering is done via an array of VertexDatum.
/// All objects *must* have textures, so that the shaders work properly.
class Object
{
  protected:
    /// An array that holds the data to be passed to OpenGL as index data
	  int* triDat;
    /// The array of vertex data that will be passed to OpenGL
  	VertexDatum* vertexData;
    /// What is the position of this?  All other points are given as relative to this centre
    Vector3 position;
    /// The game to which this object belongs.  Not really required, but might be nice at some point
    Game* game;
  	/// Vertex buffer for the vertex data
    GLuint vertexVBO;
    /// Vertex buffer for the indexes of each triangle
    GLuint indexVBO;
    /// Have these VBOs been initialised (can I destroy them?)
    bool buffersInitialised;
    /// How many triangles?
    int numberOfTriangles;
    /// How many points (not always numberOfTriangles*3)
    int numberOfPoints;
    /// Initialise the triangle and position datas
    void clearTriangleData(int,int);
    /// Adds a new vertex to the shape of this thing
    void addPoint(int,Vector3,Vector3,float,float,float);
    /// Constructs a triangle with given points
  	void addTriangle(int,int,int,int);
    /// Pushes the triangle data to the graphics card
    void pushTriangleData();
    /// Texture number.
    GLuint textureNumber;
    /// Setting uv coordinates
    void editTextureCoord(int, float, float);
    /// Repushes the vertexes to the GPU
    void updateTriangleData();
    /// Loads the object from an .obj file
    void loadFromOBJFile(const char*);
    /// Mutator for the item position
    void setPosition(Vector3);
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
