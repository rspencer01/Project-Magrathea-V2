/**
 * @file cloud.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes simple clouds
 */

#ifndef CLOUD_H
#define CLOUD_H

#include <magrathea.h>

/// A simple cloud rectangle that hovers above the landscape
class Cloud : public Object
{
  private:
    /// Create the (two) triangles
    void initialiseTriangles();
    /// Create the texture
    void updateTexture();
    /// How big is the texture
    int textureSize;
    /// The data in the texture
    unsigned char* data;
    /// The velocity of the cloud
    glm::vec3 drift;
    /// An offset for the randomness
    glm::vec3 offset;
    /// How overcast is is?
    float coverage;
  public:
	  /// Constructs
    Cloud(glm::vec3,Game*);
    /// Rendering
    void Render(int,glm::vec3);
};

#endif
