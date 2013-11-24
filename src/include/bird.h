/**
 * @file bird.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes birds
 */
#ifndef BIRD_H
#define BIRD_H

class Game;
class Bird;
#include <object.h>
#include <magrathea.h>

class Bird : public Object
{
  private:
	  void initialiseTriangles();
    float theta;
    float dihedral;
    float turnCoeff;
    Vector3 velocity;
    Vector3 forward;
    Vector3 upward;
  public:
	  /// Constructs the tree with the given coordinates
    Bird(Vector3,Game*);
    void Render(int,Vector3*);
};

#endif
