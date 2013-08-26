#include <GL/glew.h>
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

  // Lets use lines, for nicer debugging without shading and shadows
  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

}

/// Called whenever the display is resized.  Redoes the projection
/// and the display size
void resize(int width, int height)
{
  glViewport(0,0,(GLsizei)width,(GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Arguments are: Field of view, Aspect ratio, Near and then far plane
  gluPerspective(60,(GLfloat)width/(GLfloat)height,0.1,1500);
  glMatrixMode(GL_MODELVIEW);
}


/// Draws a string. x and y are percentages from the bottom left

void writeString(int x, int y, const char* format, ... )
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  // Arguments are: Field of view, Aspect ratio, Near and then far plane
  glOrtho(-1,1,-1,1,0.1,10);
  glMatrixMode(GL_MODELVIEW);


  //Format the string 
  va_list args;
  char buffer[200], *p;

  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
  // Get the right looking at point
  glLoadIdentity();
  gluLookAt(0.f,0.f,1.732f,0.f,0.f,0.f,0.f,1.f,0.f);

  //How far should we move it?
  float fx = (x-50)/50.f;
  float fy = (y-50)/50.f;

  glTranslatef(fx,fy,0);
  
  // Scale it to the right text size
  glScalef(0.0005,0.0005,1);
  
	
  int lenghOfQuote = 10;
  for (int i = 0; buffer[i]; i++)
  {
     glColor3f(1,1,1);
	 glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, buffer[i]);
  }

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}