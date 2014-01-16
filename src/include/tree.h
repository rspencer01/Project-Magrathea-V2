/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes trees
 */

#ifndef TREE_H
#define TREE_H

#include <magrathea.h>

/// A cartoonish tree, made of a number of cones.  Excellent for testing.
class Tree : public Object
{
  private:
	  void initialiseTriangles();
  public:
	  /// Constructs a cartoon tree with the given coordinates
    Tree(glm::vec3,Game*);
};


#endif
