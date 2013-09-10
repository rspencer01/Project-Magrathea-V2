/**
 * @file testobj.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section Description
 * This file describes any test object that we may use during dev to test some feature
 * It will change often.
 */

#ifndef TEST_OBJ
#define TEST_OBJ

class Game;

#include <magrathea.h>

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
