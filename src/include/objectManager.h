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
#include <set>

enum objectType 
{ bird, dynoTree, smallFern, grass_o };

/// An objectRequest is a request for the manager to create a new object
typedef struct
{
  float priority;
  /// The position of the object to be created
  Vector3* position;
  /// The parent game
  Game* game;
  /// What type of object?
  objectType type;
} objectRequest;


/// A 3D-vector imlimentation
class ObjectManager
{
  private:
    std::vector<Object*> objects;
    std::set<objectRequest,bool(*)(objectRequest,objectRequest)>* requests;
    int insertSort(Vector3);
    int furthestObject;
  public:
    ObjectManager();
    void addObject(objectType,Vector3,Game*);
    void Render(int,Vector3*);
};


#endif
