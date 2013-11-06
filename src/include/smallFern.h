/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes ferns
 */

#ifndef SMALLFERN_H
#define SMALLFERN_H

#include <magrathea.h>

/// A simple fern
class SmallFern : public Object
{
  private:
	  void initialiseTriangles();
    void makeLeaf(Vector3 pos, Vector3 dir, float width,float droopyness);
    Vector3 normal;
  public:
	  /// Constructs
    SmallFern(Vector3,Game*);
};


#endif
