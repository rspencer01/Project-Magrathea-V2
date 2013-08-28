#ifndef SKY_H
#define SKY_H

class Game;
class Sky;

#include <game.h>
#include <object.h>

class Sky : public Object
{
  public:
    Sky(Game* parent);
};

#endif
