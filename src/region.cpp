#include <stdio.h>
#include <region.h>

Region::Region(int x, int y)
{
	printf("New region at %d %d\n",x,y);
}

Region::~Region()
{
}
