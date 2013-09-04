#ifndef TERRAIN_BIT_H
#define TERRAIN_BIT_H

#include <vector3.h>

/// The terrain bit is a representation of stuff at some point
typedef struct
{
  /// The position of this piece of ground (typically 1m lateral resolution)
  Vector3* position;
  /// The normal here
  Vector3* normal;
  /// Is this point a tree?
  bool isTree;
  /// Is this point a grass piece?
  bool isGrass;
} terrainBit;

#endif
