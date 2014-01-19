/**
 * @file bird.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes birds.  At the moment, birds are simply two triangles that flap and move around the place.
 */
#ifndef BIRD_H
#define BIRD_H

#include <magrathea.h>

/// A very basic hawk like bird that circles, obeying Newtonian gravity and with a non trivial flapping motion
class Bird : public Object
{
  private:
    /// Set up the geometry
	  void initialiseTriangles();
    /// An angle used for sines and cosines etc.
    float theta;
    /// The angle between the wings
    float dihedral;
    /// A coefficient on how much the bird should circle
    float turnCoeff;
    /// Direction of motion
    glm::vec3 velocity;
    /// Forward direction (not necessarily the direction of motion)
    glm::vec3 forward;
    /// Upward
    glm::vec3 upward;
  public:
	  /// Constructs the bird
    Bird(glm::vec3,Game*);
    /// Calculates the wing angles and so forth
    void Render(int,glm::vec3);
};

#endif
