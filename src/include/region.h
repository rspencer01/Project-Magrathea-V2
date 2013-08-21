/**
 * @file region.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes the region class
 */

#ifndef REGION_H
#define REGION_H

/// A region class is a section of terrain covered by a single texture
///
/// Each region is rendered in turn.  Regions are not related to pages in size.
class region
{
  private:

  public:
	/// Constructs the region with the given 
    region(int,int);
	/// Destroys the region, freeing space
    ~region();
	/// Renders the region to the screen
    void Render();
};


#endif