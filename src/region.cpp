#include <stdio.h>
#include <gl\glew.h>
#include <gl\glut.h>
#include <region.h>

Region::Region(int x, int y)
{
	printf("New region at %d %d\n",x,y);
	origin_x = x;
	origin_y = y;
}

Region::~Region()
{
}


void Region::Render()
{
	// Translate to the origin.  We will undo this later
	glTranslatef(origin_x,0,origin_y);
	// Render the ground (well, a teapot for now)
	glutWireTeapot(1);
	// We are finished rendering.  Undo the initial translation
	glTranslatef(-origin_x,0,-origin_y);
}