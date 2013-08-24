/**
 * @file tree.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes trees
 */

#ifndef TREE_H
#define TREE_H

class Game;

#include <GL/glut.h>

#include <object.h>

class Tree : public Object
{
  private:
	/// Vertex buffer for the position of each vertex
	GLuint vertexVBO;
	/// Vertex buffer for the indexes of each triangle
	GLuint indexVBO;
	/// Populates the VBOs
	void initialiseTriangles();
	bool buffersInitialised;
  public:
	/// Constructs the tree with the given coordinates
    Tree(int,int,int,Game*);
	/// Destroys the tree, freeing space
    ~Tree();
	/// Renders the tree to the screen
    void Render();
};


#endif
