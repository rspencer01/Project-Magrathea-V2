#include <objectManager.h>
#include <stdio.h>
#include <dynoTree.h>
#include <smallFern.h>

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
  for (int i = 0;i<objects.size();i++)
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
    }
    delete req.position;
  }
}