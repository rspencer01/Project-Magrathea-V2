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
    glm::vec3 velocity;
    glm::vec3 forward;
    glm::vec3 upward;
  public:
	  /// Constructs the tree with the given coordinates
    Bird(glm::vec3,Game*);
    void Render(int,glm::vec3);
};

#endif
