#include <objectManager.h>
#include <stdio.h>
#include <dynoTree.h>
#include <smallFern.h>
#include <grass.h>

void ObjectManager::addObject(objectType type,Vector3 pos, Game* parent)
{
  objectRequest req;
  req.type = type;
  req.game = parent;
  req.position = new Vector3(pos);
  requests.push(req);
}

void ObjectManager::Render(int t, Vector3* c)
{
  int furthestObject = insertSort(*c);
  for (int i = furthestObject-1;i>=0;i--)
    objects[i]->Render(t,c);

  // Now add any items we have yet to do
  for (int i = 0;i<10;i++)
  {
    if (requests.empty())
      break;
    objectRequest req = requests.front();
    requests.pop();

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
     for (int k = i;k>0 && ((c-objects[k]->getPosition()).magnitude())<((c-objects[k-1]->getPosition()).magnitude());k--)
     {
       Object* t = objects[k];
       objects[k] = objects[k-1];
       objects[k-1] = t;
     }
  }
  for (int i = objects.size()-1;i>0;i--)
    if ((c-objects[i]->getPosition()).magnitude() < 100)
      return i+1;
  return objects.size();
}
