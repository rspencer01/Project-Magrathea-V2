float abs(float x)
{
  return x>0?x:-x;
}
/// Generates a float in the unit range with (apparantly) equal probability everywhere and random placement
/// @param n The seed
float random(int n)
{
  n=(n<<13)^n;
  int nn=(n*(n*n*15731+789221)+1376312589)&0x7fffffff;
  return abs(1.f-((float)nn/1073741824.f));
}

/// Generates 2D noise
/// @param x Seed
/// @param y Seed
inline float noise(int x,int y)
{
	int n = x + y * 674506111;
  return random(n);
 }

/// Generates smooth noise: an average of surrounding noise at x,y
inline float smoothNoise(int x, int y)
{
  /// The centres of the 3x3 block sides
	float c = (noise(x-1,y-1)+noise(x+1,y-1)+noise(x+1,y-1)+noise(x-1,y+1))/16.0f; 
  /// The corners of the same box
  float m = (noise(x-1,y)+noise(x+1,y)+noise(x,y-1)+noise(x,y+1))/8.0f;
  /// The centre
  float e = noise(x,y)/4.f;
  return e+m+c;
}

/// Creates a cubic through y0, y1, y2 and y3 and finds the value x way between y1 and y2
/// @param y_ The values to interpolate between
/// @param x  The distance (in range 0,1) between y1 and y2
inline float interpolate(float y0,float y1,float y2,float y3,float x)
{
	float P = (y3-y2)-(y0-y1);
	float Q = (y0-y1)-P;
	float R = (y2-y0);
	float S = y1;
	return P*x*x*x+Q*x*x+R*x+S;
}

/// Returns noise of non integer points
float interpolatedNoise(float x, float y)
{
	int ix = (int)x;
	float fx = x-ix;
	int iy = (int)y;
	float fy = y-iy;
  float a =  interpolate(noise(ix-1,iy-1),
 							     	 		  noise(ix,iy-1),
 								 		      noise(ix+1,iy-1),
 								 		      noise(ix+2,iy-1),fx); 
  float b =  interpolate(noise(ix-1,iy),
 							     	 		  noise(ix,iy),
 								 		      noise(ix+1,iy),
 								 		      noise(ix+2,iy),fx); 
  float c =  interpolate(noise(ix-1,iy+1),
 							     	 		  noise(ix,iy+1),
 								 		      noise(ix+1,iy+1),
 								 		      noise(ix+2,iy+1),fx); 
  float d =  interpolate(noise(ix-1,iy+2),
 							     	 		  noise(ix,iy+2),
 								 		      noise(ix+1,iy+2),
 								 		      noise(ix+2,iy+2),fx);
	return interpolate(a,b,c,d,fy);
}


/// Constructs n-th order Perlin noise 
/// @param x X coordinate
/// @param y Y coordinate
/// @param n Number of iterations to run (number of octaves)
/// @param d The decay factor
float perlinNoise(float x,float y,int n,float d)
{
	float total = 0.0;
	float freq = 1.0;
	float amp = 1.0;
	float gs = 0.0;
	while (n--)
	{
		gs += amp;
		total = total + interpolatedNoise(x*freq,y*freq)*amp;
		amp *= d;
		freq *= 2;
	}
	return total/gs;
}
