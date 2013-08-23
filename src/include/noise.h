/**
 * @file noise.h
 * @author  Robert Spencer <robert.spencer94@gmail.com>
 * @section DESCRIPTION
 *
 * This file contains a number of functions related to the generation of noise (mainly Perlin) noise.
 */
#ifndef NOISE_H
#define NOISE_H
/// Generate a random float in the range [0,1] for a seed n
float random(int n);
/// Returns non-perlin 2D noise for the position x,y
float noise(int x,int y);
/// Returns perlin noise at x,y with n iterations and degradation d
float perlinNoise(float x,float y,int n,float d);
#endif
