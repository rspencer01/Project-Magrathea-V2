#include <objectManager.h>
#include <stdio.h>
#include <dynotree.h>
#include <smallFern.h>
#include <grass.h>
#include <vector>

Vector3 camPos = Vector3();

bool compFunc(objectRequest a,objectRequest b)
{
  return a.priority<b.priority;
}


ObjectManager::ObjectManager()
{
  requests = new std::multiset<objectRequest,bool(*)(objectRequest,objectRequest)> (compFunc);
  furthestObject = 0;
}


void ObjectManager::addObject(objectType type,Vector3 pos, Game* parent)
{
  objectRequest req;
  req.type = type;
  req.game = parent;
  req.position = new Vector3(pos);
  req.priority = (camPos-pos).magnitude();
  requests->insert(req);
}



void ObjectManager::Render(int t, Vector3* c)
{
  camPos = *c;
  furthestObject = insertSort(*c);

  for (int i = furthestObject-1;i>=0;i--)
    objects[i]->Render(t,c);

  // Now add any items we have yet to do
  for (int i = 0;i<10;i++)
  {
    if (requests->empty())
      break;
    
    objectRequest req = *requests->begin();
    requests->erase(requests->begin());
    if ((camPos-*req.position).magnitude()>100)
    {
      req.priority = (camPos-*req.position).magnitude();
      requests->insert(req);
      continue;
    }


    switch (req.type)
    {
      case bird:
      {
        objects.push_back(new Bird(*req.position,req.game));
        break;
      }
      case dynoTree:
      {
        objects.push_back(new DynoTree(*req.position,req.game));
        printf("%d objects\n",objects.size());
        break;
      }
      case smallFern:
      {
        objects.push_back(new SmallFern(*req.position,req.game));
        break;
      }
      case grass_o:
      {
        objects.push_back(new Grass(*req.position,req.game));
        break;
      }

    }
    delete req.position;
  }
}

int ObjectManager::insertSort(Vector3 c)
{
  for (int i = 1;i<objects.size();i++)
  {
     if ((c-objects[i]->getPosition()).magnitude()<(c-objects[i-1]->getPosition()).magnitude())
     {
       Object* t = objects[i];
       objects[i] = objects[i-1];
       objects[i-1] = t;
     }
  }
  for (int i = objects.size()-1;i>0;i--)
    if ((c-objects[i]->getPosition()).magnitude() < 100)
      return i+1;
  return objects.size();
}
