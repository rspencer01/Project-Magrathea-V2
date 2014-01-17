/**
 * @file camera.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * The camera handles all 'movement' of the player, and renders this in opengl.
 */
#ifndef CAMERA_H
#define CAMERA_H
class Camera;
#include <magrathea.h>

/// A class that renders the scene according to some camera position and rotation
///
/// The camera class creates a matrix to move the scene so that it is that of one
/// rendered by a camera a the given position and orientation.  It also supports basic
/// fps movement (walk, up and straffe) for easy 3D world interaction
class Camera
{
  private:
	  /// The position of the camera
	  glm::vec3 Position;
    /// The upward direction
    glm::vec3 UpVector;
    /// The direction we are looking 
    glm::vec3 ViewDir;
    /// How far around have we rotated (needed for "flat" rotation")
    float RotatedX;	
    /// Where should this camera put the matrix upon rendering
    float* matrixData;
    /// Where should this camera put its position upon rendering
    float* positionData;
  public:
	  /// Initialises the camera
  	Camera(float*,float*);				
	  /// Rotates and translates the scene to the correct position.
  	void Render ( void );							
	  /// Rotate around the x axis
  	void RotateX ( float Angle );
	  /// Rotate around the y axis
  	void RotateY ( float Angle );
	  /// Rotate around the z axis
  	void RotateZ ( float Angle );
    /// Rotate in the horisontal plane
    void RotateFlat (float Angle);
  	/// Move in the direction the camera is pointing
	  void MoveForward ( float Distance );
    /// Accessor for the camera position
    glm::vec3 getPosition();
    /// Mutator for the camera position
    void setPosition(glm::vec3);
    /// Accessor for the camera viewing direction
    glm::vec3 getViewDirection();
    /// Mutator for the camera viewing direction
    void setViewDirection(glm::vec3);
};

#endif

