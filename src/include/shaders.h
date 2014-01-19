/**
 * @file    shaders.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the shader class, which is used to load shaders and set their uniform variables
 */
#ifndef SHADERS_H
#define SHADERS_H

//#include <magrathea.h>

#include <map>
#include <string>

typedef struct
{
  glm::vec4 colour;
  glm::mat4 cameraMatrix;
  glm::mat4 projectionMatrix;
  glm::mat4 lightCameraMatrix;
  glm::mat4 lightProjectionMatrix;
  glm::vec4 sunDirection;
  glm::vec4 cameraPos;
  glm::vec4 fogColour;
  float isShadow;
  float isReflection;
  float sunIntensity;
  float fog;
  float doLighting;
  float cullLevel;
  int gameTime;
  int viewWidth;
  int viewHeight;
} FrameData;

static_assert(sizeof(FrameData) == 86 * sizeof(GLfloat) + 3 * sizeof(GLint),"FrameData wrong size");

/// A shader program object handles the loading, compiling and executing of shaders (both vertex and fragment)
/// on the GPU.
class ShaderProgram
{
  private:
    /// The number OpenGL assigned to this program
    GLuint ShaderProgramID;
    /// Finds the location of a variable by name
    GLuint getVariablePosition(const char* name);
    /// A map to hold the positions in GPU memory of variables (so we don't look them up each time)
    std::map<std::string,GLuint> variableLocations;
    /// The position of the object transform matrix (changed often)
    GLuint objectDataPosition;
    /// The position of the frame information
    GLuint frameDataPosition;
    GLuint frameDataBO;
  public:
    /// Construct the program (empty and unloaded)
    ShaderProgram();
    /// Add an object
    void LoadShader(const char*,GLenum);
    /// Link all the pieces together
    void CompileAll();
    /// Actually use this shader
    void Load();
    /// Set some uniform matrix variable
    void setInt(const char* varName, unsigned int value);
    /// Function to set the object transformation matrix etc.
    void setObjectData(GLuint);
    /// Function to set the camera transformation matrix etc.
    void setFrameData();
    /// Struct containing camera transformation etc
    FrameData frameData;
};

#endif
