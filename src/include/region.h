/**
 * @file region.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes the region class
 */

#ifndef REGION_H
#define REGION_H

class Region;

#include <game.h>

/// The size of a region on a side
#define REGION_SIZE 100

/// A region class is a section of terrain covered by a single texture
///
/// Each region is rendered in turn.  Regions are not related to pages in size.
class Region
{
  private:
    Game* game;
  public:
	/// Constructs the region with the given coordinates
    Region(int,int);
	/// Destroys the region, freeing space
    ~Region();
	/// Renders the region to the screen
    void Render();
};


#endif