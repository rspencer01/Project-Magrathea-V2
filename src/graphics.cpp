#include <gl/glew.h>
#include <GL/glut.h>
#include <stdio.h>

#include <graphics.h>

/// Performs all the opengl and glut funtions to initialise the 
/// graphics.  Sets screen size, position and title bar as well
/// as setting up the fixed pipeline
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

	glewInit();
	
  // Enable all the standard pipeline things we want.  This should eventually be replaced with custom shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

/// Called whenever the display is resized.  Redoes the projection
/// and the display size
void resize(int width, int height)
{
  glViewport(0,0,(GLsizei)width,(GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Arguments are: Field of view, Aspect ratio, Near and then far plane
  gluPerspective(60,(GLfloat)width/(GLfloat)height,1.0,1500);
  glMatrixMode(GL_MODELVIEW);
}
