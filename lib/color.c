/*
 * Tatsuya Yokota
 * color.c
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "color.h"

void color_set( Color *colors, float r, float g, float b) {
  if (r < 0.0 || r > 1.0 || g < 0.0 || g > 1.0 || b < 0.0 || b > 1.0) {
    printf("rgb values not in range in color_set!\n");
    exit(-1);
  }
  
  colors->c[0] = r;
  colors->c[1] = g;
  colors->c[2] = b;
}