/**
 * @file    objectManager.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains the objectManager class
 */

#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <magrathea.h>
#include <vector>

/// A 3D-vector imlimentation
class ObjectManager
{
  private:
    std::vector<Object*> objects;
  public:
    void addObject(Vector3,Game*);
    void Render(int,Vector3*);
};


#endif
