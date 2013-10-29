#ifndef MAGRATHEA_H
#define MAGRATHEA_H

#include <GL/glew.h>
#include <GL/glut.h>

class Game;
class ShadowManager;
class ShaderProgram;
class Camera;
class Object;
class Cloud;

#include <vector3.h>

#include <object.h>
#include <noise.h>
#include <fpscounter.h>
#include <images.h>

#include <game.h>

#if defined ( WIN32 )
#define __func__ __FUNCTION__
#endif

#define DIE(_x) {fprintf(stderr,"***\nProcess called DIE on line\n  %d (%s)\nin file\n  %s \nwith message\n  \"%s\"\n***",__LINE__,__func__,__FILE__,_x);while(1);}
#define DIE2(_x,_y) {fprintf(stderr,"***\nProcess called DIE on line\n  %d (%s)\nin file\n  %s \nwith message\n  \"%s %s\"\n***",__LINE__,__func__,__FILE__,_x,_y);while(1);}

#endif
