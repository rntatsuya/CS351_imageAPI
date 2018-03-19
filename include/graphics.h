#ifndef GRAPHICS_H

#define GRAPHICS_H

#include "ppmIO.h"
#include "image.h"
#include "fractals.h"
#include "line.h"
#include "circle.h"
#include "color.h"
#include "polygon.h"
#include "vector.h"
#include "matrix.h"
#include "view.h"

/* "Higher level code that didn't/couldn't belong elsewhere" */

int checkColorEq_rc2rc(Image *src, int r1, int c1, int r2, int c2);

int checkColorEq_rc2color(Image *src, int r, int c, Color color);

void floodFill(Image *src, Point seed, Color b_color, Color f_color);

void floodFillGradient(Image *src, Point seed, Color b_color, int radius, Color f_color1, Color f_color2);

#endif