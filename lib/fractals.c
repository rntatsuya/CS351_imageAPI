#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "fractals.h"
#include "image.h"

static int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};


// takes as input floating point values indicating an anchor on the complex plane 
// and with width of the rectangle to render.
void mandelbrot( Image *dst, float x0, float y0, float dx, int renderType) {
  float dy; // height of the rect on the complex plane, computed with rows&cols of dst
  int i,j,k;
  float x,y;
  float zx0, zy0, zx1, zy1;
  int N = 500;
	
  // calculate height of the complex plane based on image:dx ratio
  dy = dx*dst->rows / dst->cols;

  // for each pixel in the image (i, j)
  for (i=0; i<dst->rows; i++) {
    for (j=0; j<dst->cols; j++) {
      // calculate (x, y) given (i, j)
      // this corresponds to cx and cy in the Mandelbrot equation
      x = dx/dst->cols * j + x0;
      y = -dy/dst->rows * i + (y0+dy);
      
      // set zx and zy to (0, 0)
      zx0 = zy0 = 0;
			
      // for some number of iterations up to N (e.g. 500)
      for (k=0; k<N; k++) {
	// iterate the Mandelbrot equation
	// make sure you do not overwrite the zx or zy values before
	// you use them in both equations
	zx1 = pow(zx0,2) - pow(zy0,2) - x; // real component 
	zy1 = 2 * zx0 * zy0 - y; // complex component
	
	// if the length of z is greater than 2.0,
	// store the number of iterations and break
	if (sqrt(pow(zx1,2) + pow(zy1,2)) > 2.0) {
	  break;
	}
				
	// update values
	zx0 = zx1;
	zy0 = zy1;
      }
      
      // color pixel (i, j) with specified rendering method
      if (renderType == 0) {
	// numIterations passing threshold 
	if (k == N) {
	  image_setc(dst, i, j, 0, 1.0);
	  image_setc(dst, i, j, 1, 1.0);
	  image_setc(dst, i, j, 2, 1.0);
	}
	else {
	  image_setc(dst, i, j, 0, 0.0);
	  image_setc(dst, i, j, 1, 0.0);
	  image_setc(dst, i, j, 2, 0.0);
	}
      }
      else if (renderType == 1) {
	// color if mod is odd
	if (k % 2 == 1) {
	  image_setc(dst, i, j, 0, 1.0);
	  image_setc(dst, i, j, 1, 1.0);
	  image_setc(dst, i, j, 2, 1.0);
	}
	else {
	  image_setc(dst, i, j, 0, 0.0);
	  image_setc(dst, i, j, 1, 0.0);
	  image_setc(dst, i, j, 2, 0.0);
	}
	
      }
      else if (renderType == 2) {
	image_setc(dst, i, j, 0, logf(logf(fabsf(zx1))));
	image_setc(dst, i, j, 1, 0.0);
	image_setc(dst, i, j, 2, logf(logf(fabsf(zx1)))*logf(fabsf(zy1)));
      }
      else if (renderType == 3) {
	image_setc(dst, i, j, 0, (k-logf(logf(sqrt(pow(zx1,2) + pow(zy1,2)))/logf(2.0)))/k);
	image_setc(dst, i, j, 1, 0.0);
	image_setc(dst, i, j, 2, 0.0);
      }
    }  
  }
}


void julia(Image *dst, float x0, float y0, float dx, float rl, float im, int renderType) {
  float dy; // height of the rect on the complex plane, computed with rows&cols of dst
  int i,j,k;
  float zx0, zy0, zx1, zy1;
  int N = 500;
	
  // calculate height of the complex plane based on image:dx ratio
  dy = dx*dst->rows / dst->cols;
  
  // for each pixel in the image (i, j)
  for (i=0; i<dst->rows; i++) {
    for (j=0; j<dst->cols; j++) {
      
      // initial start value of the system is given by the plane location
      zx0 = dx/dst->cols * j + x0;
      zy0 = -dy/dst->rows * i + (y0+dy);
      
      // for some number of iterations up to N (e.g. 500)
      for (k=0; k<N; k++) {
	// iterate the Mandelbrot equation
	// make sure you do not overwrite the zx or zy values before
	// you use them in both equations
	zx1 = pow(zx0,2) - pow(zy0,2) - rl; // real component 
	zy1 = 2 * zx0 * zy0 - im; // complex component
				
	// if the length of z is greater than 2.0,
	// store the number of iterations and break
	if (sqrt(pow(zx1,2) + pow(zy1,2)) > 2.0) {
	  break;
	}
	
	// update values
	zx0 = zx1;
	zy0 = zy1;
      }
	
      // color pixel (i, j) with specified rendering method
      if (renderType == 0) {
	// numIterations passing threshold 
	if (k == N) {
	  image_setc(dst, i, j, 0, 1.0);
	  image_setc(dst, i, j, 1, 1.0);
	  image_setc(dst, i, j, 2, 1.0);
	}
	else {
	  image_setc(dst, i, j, 0, 0.0);
	  image_setc(dst, i, j, 1, 0.0);
	  image_setc(dst, i, j, 2, 0.0);
	}
      }
      else if (renderType == 1) {
	// color if mod is odd
	if (k % 2 == 1) {
	  image_setc(dst, i, j, 0, 1.0);
	  image_setc(dst, i, j, 1, 1.0);
	  image_setc(dst, i, j, 2, 1.0);
	}
	else {
	  image_setc(dst, i, j, 0, 0.0);
	  image_setc(dst, i, j, 1, 0.0);
	  image_setc(dst, i, j, 2, 0.0);
	}			
      }
      else if (renderType == 2) {
	image_setc(dst, i, j, 0, logf(logf(fabsf(zx1))));
	image_setc(dst, i, j, 1, 0.0);
	image_setc(dst, i, j, 2, logf(logf(fabsf(zx1)))*logf(fabsf(zy1)));
      }
      else if (renderType == 3) {
	image_setc(dst, i, j, 0, (k-logf(logf(sqrt(pow(zx1,2) + pow(zy1,2)))/logf(2.0)))/k);
	image_setc(dst, i, j, 1, 0.0);
	image_setc(dst, i, j, 2, 0.0);
      }  
    }
  }
}

// get noise val from the static hash table defined above
int noise(int x, int y) {
  int tmp = hash[y % 256];
  return hash[(tmp + x) % 256];
}

// smoothing function or also known as fade function?
float fade(float x, float y, float s) {
  return  x + s * s * (3-2*s) * (y-x);
}

// use the fade and noise hash table 
float noise2d(float x, float y) {
  float x_frac = x - (int)x;
  float y_frac = y - (int)y;
  int s = noise((int)x, (int)y);
  int t = noise((int)x+1, (int)y);
  int u = noise((int)x, (int)y+1);
  int v = noise((int)x+1, (int)y+1);
  float low = fade(s, t, x_frac);
  float high = fade(u, v, x_frac);
  return fade(low, high, y_frac);
}

float perlin2d(float x, float y, float freq, int depth) {
  float xa = x*freq;
  float ya = y*freq;
  float amp = 1.0;
  float fin = 0;
  float div = 0.0;

  int i;
  for(i=0; i<depth; i++) {
    div += 256 * amp;
    fin += noise2d(xa, ya) * amp;
    amp /= 2;
    xa *= 2;
    ya *= 2;
  }

  return fin/div;
}


void perlin(Image *dst) {
  int i,j;
  float val;
	
  for (i=0; i<dst->rows; i++) {
    for (j=0; j<dst->cols; j++) {
      val = perlin2d(i, j, 0.1, 4);
      image_setc(dst, i, j, 0, val);
      image_setc(dst, i, j, 1, val);
      image_setc(dst, i, j, 2, val);
    }
  }
}


// use rand() to generate random number between 0 and 1 by dividing
// by constant RAND_MAX which is defined from the beginning
void randomNoise(Image *dst) {
  int i,j;
	
  // for each pixel in the image (i, j)
  for (i=0; i<dst->rows; i++) {
    for (j=0; j<dst->cols; j++) {
      image_setc(dst, i, j, 0, (float)rand() / (float)RAND_MAX);
      image_setc(dst, i, j, 1, (float)rand() / (float)RAND_MAX);
      image_setc(dst, i, j, 2, (float)rand() / (float)RAND_MAX);
    }
  }
}
