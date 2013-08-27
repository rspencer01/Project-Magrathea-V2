#ifndef TERRAIN_BIT_H
#define TERRAIN_BIT_H

#include <vector3.h>

/// The terrain bit is a representation of stuff at some point
typedef 
struct
{
  Vector3* position;
  Vector3* normal;
  bool isTree;
} terrainBit;

#endif
