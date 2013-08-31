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
	void initialiseTriangles();
  public:
	/// Constructs the tree with the given coordinates
    DynoTree(Vector3,Game*);
};


#endif
