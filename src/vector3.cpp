#include <math.h>

#include <vector3.h>
#include <noise.h>

// Construct a vector with the components passed.
/// @param x The x component
/// @param y The y component
/// @param z The z component
Vector3::Vector3(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

// Construct a vector given the data in an array
/// @param data The array to the data, such that data[0] is the x component etc.
Vector3::Vector3(float* data)
{
  this->x = data[0];
  this->y = data[1];
  this->z = data[2];
}

/// Constructs a vector with 0 as all its components
Vector3::Vector3()
{
  x = y = z = 0;
}

// Assign this vector
Vector3 Vector3::operator=(const Vector3& other)
{
  x = other.x;
  y = other.y;
  z = other.z;
  return *this;
}

// Add a vector to this one
Vector3 Vector3::operator+(Vector3 other)
{
  return Vector3(x+other.x,
                 y+other.y,
                 z+other.z);
}

// Subtract a vector from this one
Vector3 Vector3::operator-(Vector3 other)
{
  return Vector3(x-other.x,
                 y-other.y,
                 z-other.z);
}

// Multiply a vector by a scalar
Vector3 Vector3::operator*(float f)
{
  return Vector3(x*f,
                 y*f,
                 z*f);
}

// Divide a vector by a scalar
Vector3 Vector3::operator/(float f)
{
  return Vector3(x/f,
                 y/f,
                 z/f);
}

// Perform the dot product
float Vector3::dot(Vector3 other)
{
  return x*other.x +
         y*other.y +
         z*other.z;
}

// Perform the cross product
Vector3 Vector3::cross(Vector3 other)
{
  return Vector3(y*other.z - z*other.y,
                 z*other.x - x*other.z,
                 x*other.y - y*other.x);
}

// Find the magnitude of the vector
float Vector3::magnitude()
{
  return sqrt(x*x+y*y+z*z);
}

// Normal of this vector
Vector3 Vector3::normal()
{
  return (*this)/magnitude();
}

// Normalises this vector
void Vector3::normalise()
{
  (*this) = normal();
}


int seed = 1;
/// Constructs a random vector of magnitude 1.  Vector will be different each time of calling.
/// Not recommended for reusable content (trees etc).  Also, vector is not truly random...
Vector3 randomVector()
{
  float x,y,z;
  int s1 = seed++;
  int s2 = seed++;
  int s3 = seed++;
  x = random(s1)-0.5f;
  y = random(s2)-0.5f;
  z = random(s3)-0.5f;
  return Vector3(x,y,z).normal();
}


