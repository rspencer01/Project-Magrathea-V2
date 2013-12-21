#ifndef SHADOW_H
#define SHADOW_H

class Game;

#include <magrathea.h>

#include <shaders.h>
#include <camera.h>

class ShadowManager
{
  private:
    GLuint fboID;
    GLuint texID;
    static const int TEXTURE_SIZE = 8192;
    float maxShadowDistance;
    float minShadowDistance;
    float shadowBoxSize;
    float projMatrix[16];
    float theta;
  public:
    ShadowManager();
    Camera* camera;
    void readyForWriting(int);
    void readyForReading(ShaderProgram*);
    ShaderProgram* shader;
    void relocate(glm::vec3,int);
};

#endif