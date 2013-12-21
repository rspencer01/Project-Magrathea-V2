#ifndef GRASS_H
#define GRASS_H 

#include <magrathea.h>

#include <object.h>

class Grass : public Object
{
  private:
    void makeBunch(glm::vec3 pos);
    float theta;
  public:
    /// Constructs grass at given position, with given normal
    Grass(glm::vec3 pos, Game* parent);
    void Render(int refreshTime, glm::vec3 cameraPos);
};
#endif
