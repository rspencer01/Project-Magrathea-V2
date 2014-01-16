#ifndef TERRAIN_BIT_H
#define TERRAIN_BIT_H

#include <glm.hpp>


enum terrainType 
{ grass, stone, sand, soil };

/// The terrain bit is a representation of stuff at some point
typedef struct
{
  /// The position of this piece of ground (typically 1m lateral resolution)
  glm::vec3 position;
  /// The normal here
  glm::vec3 normal;
  /// What is the ground like here?
  terrainType type;
  /// Is this point a tree?
  bool isTree;
  /// Is this point a grass piece?
  bool isGrass;
  /// Is this point fern plant?
  bool isFern;
} terrainBit;

#endif
