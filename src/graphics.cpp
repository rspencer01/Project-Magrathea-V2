#include <GL/glut.h>
#include <stdio.h>

#include <graphics.h>

void initialiseGraphics()
{
  printf("Initialising graphics\n");
  // Initialise false command line parameters
  int argc = 0;
  char arg[10] =  "magrathea";
  char** argv = (char**)&arg;
  // Initialise GLUT with these false parameters
  glutInit(&argc,argv);
  // We want to use RGBA and a depth test
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
  // A begginning window size and position.  This will eventualy be full screen
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Magrathea");
	
  // Enable all the standard pipeline things we want.  This should eventually be replaced with custom shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}
