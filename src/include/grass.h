#ifndef GRASS_H
#define GRASS_H 

#include <magrathea.h>

#include <vector3.h>
#include <object.h>

class Grass : public Object
{
  private:
    void makeBunch(Vector3 pos);
    float theta;
  public:
    /// Constructs grass at given position, with given normal
    Grass(Vector3 pos, Game* parent);
    void Render(int refreshTime, Vector3* cameraPos);
};
#endif
