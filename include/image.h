#ifndef IMAGE_H

#define IMAGE_H

#define round(a)({(int)((a)+0.5);})

#define image_setColor(src, r1, c1, color)({\
  (src)->data[(r1)*(src)->cols + (c1)].rgb[0] = (color).c[0];\
  (src)->data[(r1)*(src)->cols + (c1)].rgb[1] = (color).c[1];\
  (src)->data[(r1)*(src)->cols + (c1)].rgb[2] = (color).c[2];\
})

#include "color.h"

typedef struct {
  float rgb[3];
  float a;
  float z;
} FPixel;

typedef struct {
  FPixel *data; // 1D array
  int rows;
  int cols;
  float maxval; // max val for a pixel  
  /* char *filename; // holds the filename of the image */
} Image;


/* Constructors and Destructors */ 
Image *image_create(int rows, int cols, float maxval);

void image_free(Image *src);

void image_init(Image *src);

int image_alloc(Image *src, int rows, int cols, float maxval);

void image_dealloc(Image *src);


/* I/O Functions */
Image *image_read(char *filename);

int image_write(Image *src, char *filename);


/* Access */
FPixel image_getf(Image *src, int r, int c);

float image_getc(Image *src, int r, int c, int b);

float image_geta(Image *src, int r, int c);

float image_getz(Image *src, int r, int c);

void image_setf(Image *src, int r, int c, FPixel val);

void image_setc(Image *src, int r, int c, int b, float val);

void image_setColorFunc(Image *src, int r, int c, Color color);

void image_setColor_scaleIntensity(Image *src, int r, int c, Color color, float scale);

void image_setColorGradient(Image *src, int r1, int c1, int r2, int c2, int p_r, int p_c, Color color1, Color color2);

void image_setColorGradientRadiant(Image *src, int r_anchor, int c_anchor, int r, int c, int radius, Color color1, Color color2);

void image_seta(Image *src, int r, int c, float val);

void image_setz(Image *src, int r, int c, float val);


/* Utility */
void image_reset(Image *src);

void image_fill(Image *src, FPixel val);

void image_fillrgb(Image *src, float r, float g, float b);

void image_filla(Image *src, float a);

void image_fillz(Image *src, float z);

#endif