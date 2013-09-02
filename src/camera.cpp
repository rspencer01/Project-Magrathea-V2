#include <GL/glut.h>
#include <math.h>
#include <camera.h>
#include <shaders.h>

// storage for Matrices

float viewMatrix[16];

Camera::Camera(Game* gm, ShaderProgram* sp)
{
  Position = Vector3(0,0,1);
  ViewDir = Vector3(0,0,-1);
  UpVector = Vector3(0,1,0);
  RotatedX = RotatedY = RotatedZ = 0;
  game = gm;
  shader = sp;
}

/// Modifys the game world transform to reflect the postion of the camera
void Camera::Render()
{
  
  Vector3 Right = ViewDir.cross(UpVector);
  Right.normalise();
  UpVector.normalise();
  ViewDir.normalise();
  viewMatrix[0] = Right.x;
  viewMatrix[4] = UpVector.x;
  viewMatrix[8] = -ViewDir.x;
  viewMatrix[12] = 0.0;

  viewMatrix[1] = Right.y;
  viewMatrix[5] = UpVector.y;
  viewMatrix[9] = -ViewDir.y;
  viewMatrix[13] = 0.0;

  viewMatrix[2] = Right.z;
  viewMatrix[6] = UpVector.z;
  viewMatrix[10] = -ViewDir.z;
  viewMatrix[14] = 0.0;

  viewMatrix[3] = -Right.dot(Position);
  viewMatrix[7] = -(UpVector.dot(Position));
  viewMatrix[11] = ViewDir.dot(Position);
  viewMatrix[15] = 1.0;

  shader->setMatrix("transformationMatrix",&viewMatrix[0]);
}

void Camera::MoveForward( float d)
{
  Position = Position + ViewDir*d;
}

void Camera::RotateY( float theta )
{
  RotatedY += theta;
  Vector3 rightDir = ViewDir.cross(UpVector);
  ViewDir = ViewDir*cos(theta) - rightDir*sin(theta);
  ViewDir.normalise();
}

void Camera::RotateX( float theta )
{
  RotatedX += theta;
  Vector3 rightDir = ViewDir.cross(UpVector);
  ViewDir = ViewDir*cos(theta) + UpVector*sin(theta);
  UpVector = rightDir.cross(ViewDir);
  ViewDir.normalise();
  UpVector.normalise();
}

void Camera::RotateFlat( float theta )
{
  float rx = RotatedX;
  RotateX(-rx);
  RotateY(theta);
  RotateX(rx);
}
