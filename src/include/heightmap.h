/**
 * @file heightmap.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file describes the heightmap functions.  These functions determine the height of a certain point
 */

#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

/// Returns the altitude of the ground at position <x,y>
float getHeightmapData(int x, int y);

#endif
