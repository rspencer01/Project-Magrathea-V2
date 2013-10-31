#include <objectManager.h>
#include <stdio.h>

void ObjectManager::addObject(objectType type,Vector3 pos, Game* parent)
{
  printf("New object at %f %f %f\n",pos.x,pos.y,pos.z);
  switch (type)
  {
    case bird:
    {
      objects.push_back(new Bird(pos,parent));
      break;
    }
  }
}

void ObjectManager::Render(int t, Vector3* c)
{
  for (int i = 0;i<objects.size();i++)
    objects[i]->Render(t,c);
}