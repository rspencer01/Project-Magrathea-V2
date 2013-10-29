/**
 * @file vector3.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the vector class, a wonderful helper for all things 3D
 */

#ifndef SHADERS_H
#define SHADERS_H

//#include <magrathea.h>

#include <map>
#include <string>


class ShaderProgram
{
  private:
    void constructProgram();
    GLuint ShaderProgramID;
    std::map<std::string,GLuint> variableLocations;
    GLuint objPos;
  public:
    ShaderProgram();
    /// Add an object
    void LoadShader(const char*,GLenum);
    /// Link all the pieces together
    void CompileAll();
    /// Actually use this shader
    void Load();
    /// Set some variable
    void setMatrix(const char*,float*);
    void setInt(const char* varName, unsigned int value);
    void setFloat(const char* varName, float value);
    void setVec3(const char*,float*);
    /// Function to set the object transformation matrix
    void setObjectMatrix(float* value);

};

#endif
