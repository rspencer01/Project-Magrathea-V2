#ifndef GRASS_H
#define GRASS_H 

#include <magrathea.h>

#include <vector3.h>
#include <object.h>

class Grass : public Object
{
  public:
    /// Constructs grass at given position, with given normal
    Grass(Vector3 pos, Vector3 norm, Game* parent,ShaderProgram*);
};
#endif
