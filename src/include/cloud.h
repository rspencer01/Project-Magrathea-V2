/**
 * @file cloud.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes clouds
 */

#ifndef CLOUD_H
#define CLOUD_H

#include <magrathea.h>

/// A simple fern
class Cloud : public Object
{
  private:
	  void initialiseTriangles();
    void updateTexture();
    int textureSize;
    unsigned char* data;
    glm::vec3 drift;
    glm::vec3 offset;
    float coverage;
  public:
	  /// Constructs
    Cloud(glm::vec3,Game*);
    void Render(int,glm::vec3);
};


#endif
