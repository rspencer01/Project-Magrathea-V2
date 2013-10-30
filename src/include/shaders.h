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

/// A shader program object handles the loading, compiling and executing of shaders (both vertex and fragment)
/// on the GPU.
class ShaderProgram
{
  private:
    /// The number OpenGL assigned to this program
    GLuint ShaderProgramID;
    /// A map to hold the positions in GPU memory of variables (so we don't look them up each time)
    std::map<std::string,GLuint> variableLocations;
    /// The position of the object transform matrix (changed often)
    GLuint objPos;
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
    void setMatrix(const char*,float*);
    /// Set some uniform integer variable
    void setInt(const char* varName, unsigned int value);
    /// Set some uniform float variable
    void setFloat(const char* varName, float value);
    /// Set some uniform vec3 variable
    void setVec3(const char*,float*);
    /// Function to set the object transformation matrix
    void setObjectMatrix(float* value);

};

#endif
