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

class DynoTree : public Object
{
  private:
    // Make new branch with start pos and direction dir of length len
    void makeBranch(Vector3 pos,Vector3 dir,float len,float width,int,bool);
    void makeLeaves(Vector3 pos,Vector3 dir,float length);
	  void initialiseTriangles();
  public:
	/// Constructs the tree with the given coordinates
    DynoTree(Vector3,Game*);
};


#endif
