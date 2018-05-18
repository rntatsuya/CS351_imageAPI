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
    printf("%.2f, %.2f, %.2f\n", r,g,b);
    exit(-1);
  }
  
  colors->c[0] = r;
  colors->c[1] = g;
  colors->c[2] = b;
}

void color_print( Color *color, FILE *fp ) {
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file!\n");
    exit(1);
  }
  
  printf("printing color\n");
  
  fprintf(fp, "Color: (%.2f, %.2f, %.2f)\n", 
  color->c[0],
  color->c[1],
  color->c[2]);
}