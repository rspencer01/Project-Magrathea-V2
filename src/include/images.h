#ifndef IMAGES_H
#define IMAGES_H

#include <magrathea.h>

/// Constructs an opengl texture from the given bitmap
GLuint textureFromBMP(const char*);
GLuint textureFromRAW(const char*);
#endif
