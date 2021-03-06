/**
 * @file region.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes the region class
 */

#ifndef REGION_H
#define REGION_H

class Game;
#include <object.h>
//#include <magrathea.h>

#include <vector>


/// The size of a region on a side
#define REGION_SIZE 30

/// A region class is a section of terrain covered by a single texture
///
/// Each region is rendered in turn.  Regions are not related to pages in size.
class Region : public Object
{
  private:
  	/// Populates the VBOs
	  void initialiseTriangles();
    ObjectManager* objectManager;
  public:
  	/// Constructs the region with the given coordinates
    Region(glm::vec3,Game*);
    /// Render the region
    void Render(int refreshTime, glm::vec3 cameraPos);
    /// Returns the X coordinate of the origin of this region
    float getOriginX();
    /// Returns the Y coordinate of the origin of this region.  This is its z coordinate in gamespace
    float getOriginY();
};


#endif
