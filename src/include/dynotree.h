/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes trees
 */

#ifndef DYNOTREE_H
#define DYNOTREE_H

class Game;

#include <GL/glut.h>

#include <object.h>

typedef struct
{
  Vector3* pos;
  Vector3* direction;
  float len;
  float width;
  bool reverseTexture;
  int basePointsIndex;
} branchStruct;

class DynoTree : public Object
{
  private:
    // Make new branch with start pos and direction dir of length len
    void makeBranch(branchStruct branch);
    void makeLeaves(Vector3 pos,Vector3 dir,float length);
	  void initialiseTriangles();
  public:
	/// Constructs the tree with the given coordinates
    DynoTree(Vector3,Game*);
};


#endif
