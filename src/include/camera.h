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
#include <vector3.h>
#include <game.h>
#include <shaders.h>

/// A helper class that renders the scene according to some camera position and rotation
///
/// The camera class invokes opengl operations to move the scene so that it is that of one
/// rendered by a camera a the given position and orientation.  It also supports basic
/// fps movement (walk, up and straffe) for easy 3D world interaction
class Camera
{
  private:
    Vector3 ViewDir;
    Vector3 UpVector;
    Game* game;
    ShaderProgram* shader;
    float RotatedX, RotatedY, RotatedZ;	
	
  public:
	  /// The position of the camera
	  Vector3 Position;
	  /// Initialises the camera to the <-1,0,0>, looking in the +x direction
  	Camera(Game*,ShaderProgram*);				
	  /// Rotates and translates the scene to the correct position.
  	void Render ( void );							

	  /// Translate the camera
  	void Move ( Vector3 Direction );
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

    float viewMatrix[16];
};

#endif

