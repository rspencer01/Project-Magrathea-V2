#ifndef SHADOW_H
#define SHADOW_H

class Game;

#include <GL\glew.h>
#include <GL\glut.h>

#include <shaders.h>
#include <camera.h>

class ShadowManager
{
  private:
    GLuint fboID;
    GLuint texID;
    static const int TEXTURE_SIZE = 1024;
    float projMatrix[16];
  public:
    ShadowManager(Game*);
    Camera* camera;
    void readyForWriting();
    void readyForReading(ShaderProgram*);
    ShaderProgram* shader;
};

#endif