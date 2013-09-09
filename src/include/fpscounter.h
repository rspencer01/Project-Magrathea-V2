/**
 * @file fpscounter.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file defines the operations to determine the frame rate
 */

#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

/// Call this function every frame to get accurate frame counts
void logFrame();
/// Returns the difference in seconds from the last frame to this
float getFrameDiff();
/// Returns the number of frames per second
float getFrameRate();

int getFrameTime();

#endif
