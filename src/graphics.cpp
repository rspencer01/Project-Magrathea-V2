#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include <graphics.h>
#include <shaders.h>

Game* game;
float projMatrix[16];

/// Performs all the opengl and glut funtions to initialise the 
/// graphics.  Sets screen size, position and title bar as well
/// as setting up the fixed pipeline
void initialiseGraphics(Game* sh)
{
  game = sh;
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

  // Initialise glew.  If there is an error, report it
  GLenum res = glewInit();
  if (res != GLEW_OK)
  {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
    return;
  }
	
  // Enable all the standard pipeline things we want.  This should eventually be replaced with custom shaders
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // Lets enable alpha blending
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // Draw all transparancies except completely invisibles
  glAlphaFunc ( GL_GREATER, (GLclampf)0.01 ) ;
  glEnable ( GL_ALPHA_TEST ) ;

  // Fill the polygons, please
  glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

  // Lets not display a cursor
  glutSetCursor(GLUT_CURSOR_NONE);

  // Set up all the vertex attribut arrays for rendering later on...
  glEnableVertexAttribArrayARB(0);
  glEnableVertexAttribArrayARB(1);
  glEnableVertexAttribArrayARB(2);
  glEnableVertexAttribArrayARB(3);
  glEnableVertexAttribArrayARB(4);
}

/// Builds a projection matrix
void BuildPerspProjMat(float *m, float fov, float aspect, float znear, float zfar)
{
  m[0]  = (float)(1.f/(aspect * tan(fov*3.141592/360.0)));
  m[4]  = 0;
  m[8]  = 0;
  m[12]  = 0;

  m[1]  = 0;
  m[5]  = (float)(1.f/tan(fov*3.141592/360.0));
  m[9]  = 0;
  m[13]  = 0;

  m[2]  = 0;
  m[6]  = 0;
  m[10] = (-zfar)/(zfar-znear);
  m[14] = -1;

  m[3] = 0;
  m[7] = 0;
  m[11] = -zfar*znear/(zfar-znear);
  m[15] = 0;
}

/// Called whenever the display is resized.  Redoes the projection
/// and the display size
void resize(int width, int height)
{
  // Set the size of the viewport
  glViewport(0,0,(GLsizei)width,(GLsizei)height);
  game->mainShader->frameData.viewHeight = height;
  game->mainShader->frameData.viewWidth = width;
  // Construct the projection matrix ...
  BuildPerspProjMat(projMatrix,20.f, float(width)/height, 2.f, 100.f);
  // ... and push it to the shaders
  memcpy(&(game->mainShader->frameData.projectionMatrix),projMatrix,16*sizeof(float));
  game->mainShader->setFrameData();
}


/// Draws a formatted string. x and y are percentages from the bottom left
/// @param x Coordinate from the left
/// @param y Coordinate from the bottom
/// @param format The format of the string
/// @param ... Arguments
void writeString(int x, int y, const char* format, ... )
{
  //Format the string 
  va_list args;
  char buffer[200];
  va_start(args, format);
  vsprintf(buffer, format, args);
  va_end(args);
 
  // Save the current projection
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  // Arguments are: Field of view, Aspect ratio, Near and then far plane
  glOrtho(-1,1,-1,1,0.1,10);
  // Now we will be drawing
  glMatrixMode(GL_MODELVIEW);

  // Get the right looking at point
  glLoadIdentity();
  gluLookAt(0.f,0.f,1.732f,0.f,0.f,0.f,0.f,1.f,0.f);

  //How far should we move it?
  float fx = (x-50)/50.f;
  float fy = (y-50)/50.f;
  glTranslatef(fx,fy,0);
  
  // Scale it to the right text size
  glScalef((GLfloat)0.0005,(GLfloat)0.0005,(GLfloat)1);

  // Some nice white text, please
  glColor4f(1.f,1.f,1.f,1.f);

  // Now create the characters
  for (int i = 0; buffer[i]; i++)
	  glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, buffer[i]);

  // Now we are done, get the projection matrix back
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  // And get back into model mode
  glMatrixMode(GL_MODELVIEW);
}
