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
class Object;

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm.hpp>

#include <shaders.h>

#define OT_STANDARD_OBJECT 0;
#define OT_WATER 1;

/// \brief Contains all the information passed to the shaders.
///
/// This is passed to the vertex shader via four (currently) vertex attributes, one for each major attribute.
/// Soon it will be defined in the shader and then it will just be passed as flat data through one.
/// TODO Pass this in one data stream for GLSL portability
typedef struct
{
  /// The position of the vertex
  glm::vec3 position;
  /// The vertex colour
  glm::vec4 colour;
  /// The normal at the vertex
  glm::vec3 normal;
  /// Thecoordinates of the texture
  glm::vec2 texture;
  /// Texture mixing parts.  A value of less than 0 in the x axis indicates not texture mixing
  glm::vec4 texMix;
} VertexDatum;

typedef struct
{
  glm::mat4 transformMatrix;
  glm::vec4 objectColour;
  float shinyness;
  int objectType;
  int isGrassy;
} ObjectData;

// Check that the above structs are the right size
static_assert(sizeof(VertexDatum) == sizeof(GLfloat) * 16, "VertexDatum incorrect size");
static_assert(sizeof(ObjectData) == sizeof(GLfloat) * 21 + 2* sizeof(GLuint), "ObjectData incorrect size");

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
    glm::vec3 position;
    /// The direction we are facing (or the direction towards the camera in billboard mode)
    glm::vec3 forward;
    /// The upward direction
    glm::vec3 up;
    /// The right direction
    glm::vec3 right;
    /// The game to which this object belongs.  Used to access shaders
    Game* game;
  	/// Vertex buffer for the vertex data
    GLuint vertexVBO;
    /// Vertex buffer for the indexes of each triangle
    GLuint indexVBO;
    /// Object/Material settings
    GLuint objectBO;
    /// Have these VBOs been initialised (can I destroy them?)
    bool buffersInitialised;
    /// How many triangles?
    int numberOfTriangles;
    /// How many points (not always numberOfTriangles*3)
    int numberOfPoints;
    /// Is this object billboarded (always facing the camera)?
    bool billboard;
    /// A testing number for slew
    float xySlew;
    /// Initialise the triangle and position datas
    void clearTriangleData(int,int);
    /// Adds a new vertex to the shape of this thing
    void addPoint(int,glm::vec3,glm::vec3,float,float,float);
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
    void setPosition(glm::vec3);
    /// Rotates the object so that it matches the new axis
    void rotate(glm::vec3,glm::vec3);
    /// Sets the object colour
    void setColour(glm::vec4);
    /// The function to populate the above
    void updateMatrix();
    /// Sets a point's mix of textures
    void setTextureMix(int,float,float,float,float);
    /// Free the space of the vertices
    void freeze();
    /// The transformation, colour etc for this object
    ObjectData objectData;
    /// Send all the above to the shader
    void updateObjectBO();
  public:
	  /// Constructs the object with the given coordinates and in the given game
    Object(glm::vec3,Game*);
  	/// Destroys the Object, freeing space
    virtual ~Object();
  	/// Renders the Object to the screen
    virtual void Render(int refreshTime, glm::vec3 cameraPos);
  	/// Accessor for the item position
    glm::vec3 getPosition();
};


#endif
