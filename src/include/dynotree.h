/**
 * @file dynoTree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes dynamically generated trees
 */
#ifndef DYNOTREE_H
#define DYNOTREE_H

#include <magrathea.h>

class DynoTree : public Object
{
  private:
    // Make new branch with start pos and direction dir of length len
    void makeBranch(Vector3 pos,Vector3 dir,float len,float width,int,bool);
    // Populates a branch with leaves
    void makeLeaves(Vector3 pos,Vector3 dir,float length);
    // Starts the whole process
	  void initialiseTriangles();
  public:
	  /// Constructs the tree with the given coordinates
    DynoTree(Vector3,Game*);
};

#endif
