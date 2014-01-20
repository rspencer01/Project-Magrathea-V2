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
{ bird, dynoTree, smallFern };

/// An objectRequest is a request for the manager to create a new object
typedef struct
{
  float priority;
  /// The position of the object to be created
  glm::vec3 position;
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
    std::multiset<objectRequest,bool(*)(objectRequest,objectRequest)>* requests;
    int insertSort(glm::vec3);
    int furthestObject;
  public:
    ObjectManager();
    void addObject(objectType,glm::vec3,Game*);
    void Render(int,glm::vec3);
};


#endif
