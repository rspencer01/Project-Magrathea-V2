/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 */

#ifndef TEST_OBJ
#define TEST_OBJ

class Game;

#include <magrathea.h>

#include <object.h>

/// A test object used for all kinds of feature testing
class TestObj : public Object
{
  private:
	  void initialiseTriangles();
  public:
	  /// Constructs the object
    TestObj(Game*);
};


#endif
