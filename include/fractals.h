#ifndef FRACTALS_H

#define FRACTALS_H

#include "image.h"

/* Fractal generation */
void mandelbrot( Image *dst, float x0, float y0, float dx, int renderType);

void julia(Image *dst, float x0, float y0, float dx, float rl, float im, int renderType);

void randomNoise(Image *dst);

void perlin(Image *dst);

float perlin2d(float x, float y, float freq, int depth);

float noise2d(float x, float y);

float fade(float x, float y, float s);

int noise(int x, int y);

#endif