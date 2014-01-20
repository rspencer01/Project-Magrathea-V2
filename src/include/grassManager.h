/**
 * @file    objectManager.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the objectManager class
 */

#ifndef GRASSMANAGER_H
#define GRASSMANAGER_H

#include <magrathea.h>
#include <vector>
#include <set>

class GrassManager
{
  private:
    Game* game;
    ShaderProgram* shader;
  public:
    GrassManager(Game*);
    void Render(int,glm::vec3);
};


#endif
