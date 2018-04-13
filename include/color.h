#ifndef COLOR_H

#define COLOR_H

#include <stdio.h>

typedef struct {
  float c[3];
} Color;


void color_set( Color *colors, float r, float g, float b);

void color_print( Color *c, FILE *fp );

#endif