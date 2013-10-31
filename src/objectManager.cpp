#include <objectManager.h>
#include <stdio.h>

void ObjectManager::addObject(Vector3 pos, Game* parent)
{
  printf("New object at %f %f %f\n",pos.x,pos.y,pos.z);
  objects.push_back(new Bird(pos,parent));
}

void ObjectManager::Render(int t, Vector3* c)
{
  for (int i = 0;i<objects.size();i++)
    objects[i]->Render(t,c);
}