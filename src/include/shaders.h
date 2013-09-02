/**
 * @file vector3.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the vector class, a wonderful helper for all things 3D
 */

#ifndef SHADERS_H
#define SHADERS_H

#include <gl\glut.h>


class ShaderProgram
{
  private:
    void constructProgram();
    GLuint ShaderProgramID;
  public:
    ShaderProgram();
    /// Add an object
    void LoadShader(const char*,GLenum);
    /// Link all the pieces together
    void CompileAll();
    /// Actually use this shader
    void Load();
};


void loadShaders();
void setTransformationMatrix(float*);
void setProjectionMatrix(float*);
#endif
