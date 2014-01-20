#include <objectManager.h>
#include <stdio.h>
#include <dynotree.h>
#include <smallFern.h>
#include <vector>

glm::vec3 camPos = glm::vec3();

bool compFunc(objectRequest a,objectRequest b)
{
  return a.priority<b.priority;
}


ObjectManager::ObjectManager()
{
  requests = new std::multiset<objectRequest,bool(*)(objectRequest,objectRequest)> (compFunc);
  furthestObject = 0;
}


void ObjectManager::addObject(objectType type,glm::vec3 pos, Game* parent)
{
  objectRequest req;
  req.type = type;
  req.game = parent;
  req.position = pos;
  req.priority = (camPos-pos).length();
  requests->insert(req);
}



void ObjectManager::Render(int t, glm::vec3 c)
{
  //return;
  camPos = c;
  furthestObject = insertSort(c);
  for (int i = objects.size()-1;i>=0;i--)
    objects[i]->Render(t,c);
  
  //printf("%lu objects\n",(unsigned long)objects.size());
  // Now add any items we have yet to do
  for (int i = 0;i<10;i++)
  {
    if (requests->empty())
      break;
    
    objectRequest req = *requests->begin();
    requests->erase(requests->begin());

    switch (req.type)
    {
      case bird:
      {
        objects.push_back(new Bird(req.position,req.game));
        break;
      }
      case dynoTree:
      {
        objects.push_back(new DynoTree(req.position,req.game));
        break;
      }
      case smallFern:
      {
        objects.push_back(new SmallFern(req.position,req.game));
        break;
      }
    }
  }
}

int ObjectManager::insertSort(glm::vec3 c)
{
  for (unsigned int i = 1;i<objects.size();i++)
  {
     if (glm::length(c-objects[i]->getPosition()) < glm::length(c-objects[i-1]->getPosition()))
     {
       Object* t = objects[i];
       objects[i] = objects[i-1];
       objects[i-1] = t;
     }
  }
  return objects.size();
}
