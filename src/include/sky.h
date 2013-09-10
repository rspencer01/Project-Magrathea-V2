#ifndef SKY_H
#define SKY_H

class Game;
class Sky;

#include <magrathea.h>

#include <game.h>
#include <object.h>

class Sun : public Object
{
  private:
    Vector3 centre;
    float theta;
  public:
    Sun(Vector3 pos,Game* parent,ShaderProgram*);
    void Render(int);
};

class Sky : public Object
{
  private:
    Sun* sun;
  public:
    Sky(Game* parent,ShaderProgram*);
    void Render(int);
};

#endif
