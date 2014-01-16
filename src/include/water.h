/**
 * @file testobj.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section Description
 * This file describes the water.
 */

#ifndef WATER_H
#define WATER_H

class Game;

#include <magrathea.h>

/// A test object used for all kinds of feature testing
class Water : public Object
{
  private:
	  void initialiseTriangles();
    GLuint reflectiveTexture;
    GLuint reflectiveBuffer;
    GLuint reflectiveDepthBuffer;
  public:
	  /// Constructs the object
    Water(glm::vec3,Game*);
    void Render(int refreshTime, glm::vec3 cameraPos);
};


#endif
