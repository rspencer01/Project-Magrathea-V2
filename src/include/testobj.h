/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes trees
 */

#ifndef TEST_OBJ
#define TEST_OBJ

class Game;

#include <GL/glut.h>

#include <object.h>

class TestObj : public Object
{
  private:
	void initialiseTriangles();
  public:
	/// Constructs the tree with the given coordinates
    TestObj(Game*);
};


#endif
