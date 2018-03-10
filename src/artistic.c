/*
  Assignment 4, required image 1

  C version
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

/*
  Program to test polygon functionality
*/
int main(int argc, char *argv[]) {
  Image *src;
  const int rows = 1000;
  const int cols = 1000;
  Color Red;
  Color Orange;
  Color White;
  Color Blue;
  
  srand(42);

  color_set(&Red, 0.9, 0.2, 0.1 );
  color_set(&Orange, 0.95, 0.7, 0.3 );
  color_set(&White, 1.0, 1.0, 1.0 );
  color_set(&Blue, 0.2, 0.1, 0.95 );

  src = image_create(rows, cols, 255);

  Circle circle;
  Point p_circle;

  point_set2D( &p_circle, 500, 500 );
  circle_set( &circle, p_circle, 100 );
  circle_drawGradientFill( &circle, src, 0, 0, Red, Blue );

  printf("Writing artistic extension\n");
  image_write(src, "artistic.ppm");

  image_free(src);

  return(0);
}
