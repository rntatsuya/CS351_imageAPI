#ifndef COLOR_H

#define COLOR_H

typedef struct {
  float c[3];
} Color;


void color_set( Color *colors, float r, float g, float b);

#endif