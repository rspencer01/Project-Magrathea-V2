/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes ferns
 */

#ifndef FERN_H
#define FERN_H

#include <magrathea.h>

/// A simple fern
class Fern : public Object
{
  private:
	  void initialiseTriangles();
  public:
	  /// Constructs
    Fern(Vector3,Game*);
};


#endif
