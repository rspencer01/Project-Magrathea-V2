/**
 * @file vector3.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the vector class, a wonderful helper for all things 3D
 */

#ifndef VECTOR3_H
#define VECTOR3_H

/// A simple 3D-vector imlimentation
class Vector3
{
  public:
    /// The x component of the vector
    float x;
	/// The y component of the vector
    float y;
	/// The z component of the vector
    float z;
	/// Construct a vector object with the given components
	Vector3(float x,float y,float z);
	/// Construct a vector with the array [x,y,z] components
    Vector3(float*);
	/// Construc the null vector
    Vector3();
	/// Assigns this vector to the other vector
    Vector3 operator=(const Vector3&);
	/// Adds a vector
    Vector3 operator+(Vector3);
	/// Subtracts a vector
    Vector3 operator-(Vector3);
	/// Performs a multiplication with a scalar
    Vector3 operator*(float);
	/// Performs a dot product with the other vector
    float dot(Vector3);
	/// Returns the magnitude of the vector
    float magnitude();
	/// Turns the vector into a unit vector
    void normalise();
};

#endif