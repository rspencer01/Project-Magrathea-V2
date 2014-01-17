#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include <camera.h>
#include <shaders.h>

/// Construct a new camera, editing the "transformationMatrix" variable of the given shader program
/// @param gm The game in which this camera resides
/// @param sp The shader to which this camera belongs
Camera::Camera(float* matrix, float* position)
{
  // Initialise to some useful directions
  Position = glm::vec3(0,0,1);
  ViewDir = glm::vec3(0,0,-1);
  UpVector = glm::vec3(0,1,0);
  // No rotation yet
  RotatedX = 0;
  // Remember the environment
  matrixData = matrix;
  positionData = position;
}

/// Modifys the game world transform to reflect the postion of the camera.
/// Actually constructs a viewing matrix.
void Camera::Render()
{
  // Calculate the right vector
  glm::vec3 Right = glm::cross(ViewDir,UpVector);
  // Normalise all the other vectors
  Right = glm::normalize(Right);
  UpVector = glm::normalize(UpVector);
  ViewDir = glm::normalize(ViewDir);

  // Construct a matrix that transforms the object in the correct way
  matrixData[0] = Right.x;
  matrixData[1] = UpVector.x;
  matrixData[2] = -ViewDir.x;
  matrixData[3] = 0.f;

  matrixData[4] = Right.y;
  matrixData[5] = UpVector.y;
  matrixData[6] = -ViewDir.y;
  matrixData[7] = 0.f;

  matrixData[8] = Right.z;
  matrixData[9] = UpVector.z;
  matrixData[10] = -ViewDir.z;
  matrixData[11] = 0.f;

  matrixData[12] = -glm::dot(Right,Position);
  matrixData[13] = -glm::dot(UpVector,Position);
  matrixData[14] = glm::dot(ViewDir,Position);
  matrixData[15] = 1.f;

  // Update the position of the camera, also
  positionData[0] = Position.x;
  positionData[1] = Position.y;
  positionData[2] = Position.z;
}

/// Moves the camera in the direction it is facing
/// @param d The distance to move
void Camera::MoveForward( float d)
{
  Position = Position + ViewDir*d;
}

/// Rotates the camera about the Y axis (horisontal)
/// @param theta The angle to turn by
void Camera::RotateY( float theta )
{
  // Calculate the right hand vector
  glm::vec3 rightDir = glm::normalize(glm::cross(ViewDir,UpVector));
  ViewDir = glm::normalize(ViewDir*cos(theta) - rightDir*sin(theta));
}

/// Rotates the camera about the X axis (vertical)
/// @param theta The angle to turn by
void Camera::RotateX( float theta )
{
  // Calculate the right hand vector
  glm::vec3 rightDir = glm::normalize(glm::cross(ViewDir,UpVector));
  ViewDir = ViewDir*cos(theta) + UpVector*sin(theta);
  UpVector = glm::cross(rightDir,ViewDir);
  ViewDir  = glm::normalize(ViewDir);
  UpVector = glm::normalize(UpVector);
  // Log this rotation
  RotatedX += theta;
}

/// Rotates in the xz-plane.
/// @param theta The angle to turn by
void Camera::RotateFlat( float theta )
{
  // We are going to antirotate up to the horison, do a horisontal rotation and then look down again
  float rx = RotatedX;
  // Look up...
  RotateX(-rx);
  // Turn...
  RotateY(theta);
  // Look down.
  RotateX(rx);
}

glm::vec3 Camera::getPosition()
{
  return Position;
}

void Camera::setPosition(glm::vec3 newPos)
{
  Position = newPos;
}

glm::vec3 Camera::getViewDirection()
{
  return ViewDir;
}

void Camera::setViewDirection(glm::vec3 newDir)
{
  ViewDir = newDir;
}