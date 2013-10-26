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
    Vector3 drift;
    Vector3 offset;
    float coverage;
  public:
	  /// Constructs
    Cloud(Vector3,Game*);
    void Render(int,Vector3*);
};


#endif
