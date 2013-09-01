#include <GL/glut.h>
#include <math.h>
#include <camera.h>
#include <shaders.h>

Camera::Camera(Game* gm)
{
  Position = Vector3(-1,0,0);
  ViewDir = Vector3(1,0,0);
  UpVector = Vector3(0,1,0);
  RotatedX = RotatedY = RotatedZ = 0;
  game = gm;
}

/// Modifys the game world transform to reflect the postion of the camera
void Camera::Render()
{
  // Find the point we are looking at
  Vector3 viewPoint = Position + ViewDir;
  float tm[16];
  for (int i = 0;i<16;i++)
    tm[i] = 0;
  tm[0] = 1;
  tm[5] = 0.5;
  tm[10] = 1;
  tm[15] = 1;

  setTrans(&tm[0]);
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
