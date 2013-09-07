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
    int sinceLastRefresh;
    float theta;
  public:
    ShadowManager();
    Camera* camera;
    bool readyForWriting(int);
    void readyForReading(ShaderProgram*);
    ShaderProgram* shader;
    void relocate(Vector3,int);
};

#endif