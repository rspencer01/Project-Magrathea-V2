#ifndef SKY_H
#define SKY_H

class Game;
class Sky;
class Stars;
#include <magrathea.h>

#include <game.h>
#include <object.h>

class Sun : public Object
{
  private:
    glm::vec3 centre;
    float theta;
  public:
    Sun(glm::vec3 pos,Game* parent);
    void Render(int,glm::vec3);
};

class Stars : public Object
{
  private:
    float theta;
  public:
    Stars(Game* parent);
    void Render(int,glm::vec3);
};

class Sky : public Object
{
  private:
    Sun* sun;
    Stars* stars;
    float theta;
  public:
    Sky(Game* parent);
    void Render(int,glm::vec3);
};

#endif
