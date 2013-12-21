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
    void makeLeaf(glm::vec3 pos, glm::vec3 dir, float width,float droopyness);
    glm::vec3 normal;
  public:
	  /// Constructs
    SmallFern(glm::vec3,Game*);
};


#endif
