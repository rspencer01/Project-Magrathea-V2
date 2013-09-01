#include <GL/glut.h>
#include <math.h>
#include <camera.h>
#include <shaders.h>

// storage for Matrices
float projMatrix[16];
float viewMatrix[16];

 void BuildPerspProjMat(float *m, float fov, float aspect, float znear, float zfar)
 {
  float ymax = znear * tan(fov * 3.141592/360.0);
  float ymin = -ymax;
  float xmax = ymax * aspect;
  float xmin = ymin * aspect;

  float width = xmax - xmin;
  float height = ymax - ymin;

  float depth = zfar - znear;
  float q = -(zfar + znear) / depth;
  float qn = -2 * (zfar * znear) / depth;

  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;

  m[0]  = w;
  m[1]  = 0;
  m[2]  = 0;
  m[3]  = 0;

  m[4]  = 0;
  m[5]  = h;
  m[6]  = 0;
  m[7]  = 0;

  m[8]  = 0;
  m[9]  = 0;
  m[10] = q;
  m[11] = -1;

  m[12] = 0;
  m[13] = 0;
  m[14] = qn;
  m[15] = 0;
 }


Camera::Camera(Game* gm)
{
  Position = Vector3(0,0,1);
  ViewDir = Vector3(0,0,-1);
  UpVector = Vector3(0,1,0);
  RotatedX = RotatedY = RotatedZ = 0;
  game = gm;
}


/// Modifys the game world transform to reflect the postion of the camera
void Camera::Render()
{
  BuildPerspProjMat(projMatrix,53.13f, 2.0/3.0, 1.0f, 100.0f);
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


  setTrans(&viewMatrix[0]);
  setProj(&projMatrix[0]);
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
