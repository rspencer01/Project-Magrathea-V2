/**
 * @file    magrathea.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file is very important. It holds forward definitions for all the classes (so that classes can 
 * have pointers to classes they don't know about yet, and so that circular definitions don't arise).  
 * It also includes all the header files of important classes and some definitions for useful macros 
 * and variables that the whole program may need to know about.
 *
 * One notable use of this file is that including it supercedes including glew and glut files. 
 *
 * However, it is pig-ugly and there is no standard of when to include it and when not.
 * If someone has an idea of what to do here, please fix me.
 */
#ifndef MAGRATHEA_H
#define MAGRATHEA_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <log.h>

class Game;
class ShadowManager;
class ShaderProgram;
class Camera;
class Object;
class Cloud;
class ObjectManager;
class GrassManager;

#include <object.h>
#include <noise.h>
#include <fpscounter.h>
#include <images.h>


#include <game.h>

#if defined ( WIN32 )
#define __func__ __FUNCTION__
#endif

#define DIE(_x) {loge.log("\n***\nProcess called DIE on line\n  %d (%s)\nin file\n  %s \nwith message\n  \"%s\"\n***",__LINE__,__func__,__FILE__,_x);while(1);}
#define DIE2(_x,_y) {loge.log("\n***\nProcess called DIE on line\n  %d (%s)\nin file\n  %s \nwith message\n  \"%s %s\"\n***",__LINE__,__func__,__FILE__,_x,_y);while(1);}
#define DIE3(_x,_y,_z) {loge.log("\n***\nProcess called DIE on line\n  %d (%s)\nin file\n  %s \nwith message\n  \"%s %s %s\"\n***",__LINE__,__func__,__FILE__,_x,_y,_z);while(1);}
#endif
