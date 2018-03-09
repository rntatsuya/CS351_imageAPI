/*
 * Tatsuya Yokota
 * image.c
 * Contains the base image functions 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "math_aprox.h"
#include "image.h"
#include "ppmIO.h"
#include "color.h"

#define USECPP 0

/* Allocates an Image structure and initializes the top level fields to appropriate values.
 * Allocates space for an image of the specified size, unless either rows or cols is 0.
 * Returns a pointer to the allocated Image structure. Returns a NULL pointer if the operation
 * fails.
 */
Image *image_create(int rows, int cols, float maxval) {
  if (rows <= 0 || cols <= 0) {
    printf("rows or cols cannot be negative in image_create!\n");
    return NULL;
  }
  
  Image *src = malloc(sizeof(Image));
  
  if (!src) {
    printf("Ran out of memory while mallocing Image struct in image_create!\n");
    return NULL;
  }
  src->rows = rows;
  src->cols = cols;
  src->maxval = maxval;
  src->data = malloc(sizeof(FPixel) * rows * cols);
  
  if (!src->data) {
    free(src);
    return NULL;
  }
  return src;
}

/* de-allocates image data and frees the Image structure. */
void image_free(Image *src) {
  if (src->data) {
    free(src->data);
  }
  if (src) {
    free(src);
  }
}

/* given an uninitialized Image structure, sets the rows and cols fields to zero and 
 * the data field to NULL.
 */
void image_init(Image *src) {
  src->rows = 0;
  src->cols = 0;
  src->maxval = 0;
  src->data = NULL;
}

/* allocates space for the image data given rows and columns and initializes the image data
 * to appropriate values, such as 0.0 for RGB and 1.0 for A and Z. Returns 0 if the operation
 * is successful. Returns a non-zero value if the operation fails. This function should 
 * free existing memory if rows and cols are both non-zero.
*/
int image_alloc(Image *src, int rows, int cols, float maxval) {
  if (rows < 0 || cols < 0) {
    printf("rows or cols cannot be negative in image_alloc!\n");
    return 1;
  }
  else if (src->rows != 0 || src->cols != 0) {
    free(src->data);
  }

  src->rows = rows;
  src->cols = cols;
  src->maxval = maxval;
  src->data = malloc(sizeof(FPixel) * rows * cols);
  
  // see if we ran out of memory
  if (!src->data) {
    printf("Ran out of memory while mallocing FPixel array in image_alloc!\n");
    return 1;
  }

  // loop through every pixel
  int i;
  for (i=0; i<rows*cols; i++) {
    src->data[i].rgb[0] = 0.0;
    src->data[i].rgb[1] = 0.0;
    src->data[i].rgb[2] = 0.0;
    // init alpha and depth
    src->data[i].a = src->data[i].z = 1.0;
  }
  
  return 0;
}

/* de-allocates image data and resets the Image structure fields. The function
 * does not free the Image structure */
void image_dealloc(Image *src) {
  if (src->data) {
    free(src->data);
  }
  image_init(src);
}

/* – reads a PPM image from the given filename.
 * Initializes the alpha channel to 1.0 and the z channel to 1.0. 
 * Returns a NULL pointer if the operation fails
 */
Image *image_read(char *filename) {
  Pixel *image;
  Image *src;
  int rows, cols, colors;
  long imagesize;
  long i;
  
  image = readPPM(&rows, &cols, &colors, filename);
  
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", filename);
    exit(-1);
  }
	
  // construct image struct
  src = image_create(rows, cols, (float)colors);
  
  if (!src) {
    fprintf(stderr, "Unable to allocate memory to Image pointer\n");
    exit(-1);
  }
	
  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  /* reassign pixel values to image struct data field */
  for(i=0;i<imagesize;i++) {
    src->data[i].rgb[0] = image[i].r;
    src->data[i].rgb[1] = image[i].g;
    src->data[i].rgb[2] = image[i].b;
    src->data[i].a = 1.0;
    src->data[i].z = 1.0;
  }
  
  free(image);
  
  return src;
}

/* writes a PPM image to the given filename. Returns 0 on success. */
int image_write(Image *src, char *filename) {
  Pixel *image;
  int rows, cols; 
  int colors;
  long imagesize;
  long i;
  
  rows = src->rows;
  cols = src->cols;
  colors = (int)src-> maxval;
  imagesize = rows * cols;
  
  image = (Pixel *)malloc(sizeof(Pixel) * imagesize);
  
  for (i=0; i<imagesize; i++) {
    image[i].r = src->data[i].rgb[0]*colors;
    image[i].g = src->data[i].rgb[1]*colors;
    image[i].b = src->data[i].rgb[2]*colors;
  }
	
  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, filename);

  free(image);  

  return 0;
}


/* returns the FPixel at (r, c). */
FPixel image_getf(Image *src, int r, int c) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_getf\n");
  }
  return src->data[r*src->cols + c];
}

/* returns the value of band b at pixel (r, c). */
float image_getc(Image *src, int r, int c, int b) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_getc\n");
  }
  if (b < 0 || b > 2) {
    printf("Specified band out of bounds at image_getc, select either 0, 1, or 2\n");
  }
  return src->data[r*src->cols + c].rgb[b];
}

/* – returns the alpha value at pixel (r, c). */
float image_geta(Image *src, int r, int c) {
  return src->data[r*src->cols + c].a;
}

/* returns the depth value at pixel (r, c). */
float image_getz(Image *src, int r, int c) {
  return src->data[r*src->cols + c].z;
}



/* sets the values of pixel (r,c) to the FPixel val */
void image_setf(Image *src, int r, int c, FPixel val) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_setf\n");
    return;
  }
  src->data[r*src->cols + c] = val;
}

/* sets the value of pixel (r, c) band b to val. */
void image_setc(Image *src, int r, int c, int b, float val) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_setc\n");
    return;
  }
//   printf("Adding: %f to (%d,%d,%d)\n", val, c, r,b);
  src->data[r*src->cols + c].rgb[b] = val;
}

// WARNING: check if r and c are in Image src's boundaries before calling this 
void image_setColorFunc(Image *src, int r, int c, Color color) {
  src->data[r*src->cols + c].rgb[0] = color.c[0];
  src->data[r*src->cols + c].rgb[1] = color.c[1];
  src->data[r*src->cols + c].rgb[2] = color.c[2];
}

void image_setColorGradient(Image *src, int r_anchor, int c_anchor, int r, int c, int radius, Color color1, Color color2) {
  // get distance
  float d = __sqrt((float)(c - c_anchor) * (c - c_anchor) + (r - r_anchor) * (r - r_anchor));
  float alpha = d / radius;
  src->data[r*src->cols + c].rgb[0] = color1.c[0] * (1 - alpha) + color2.c[0] * alpha;
  src->data[r*src->cols + c].rgb[1] = color1.c[1] * (1 - alpha) + color2.c[1] * alpha;
  src->data[r*src->cols + c].rgb[2] = color1.c[2] * (1 - alpha) + color2.c[2] * alpha;
}

void image_setColor_scaleIntensity(Image *src, int r, int c, Color color, float scale) {
  src->data[r*src->cols + c].rgb[0] = color.c[0] * scale;
  src->data[r*src->cols + c].rgb[1] = color.c[1] * scale;
  src->data[r*src->cols + c].rgb[2] = color.c[2] * scale;
}

/* sets the alpha value of pixel (r, c) to val. */
void image_seta(Image *src, int r, int c, float val) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_seta\n");
    return;
  }
  src->data[r*src->cols + c].a = val;
}

/* sets the depth value of pixel (r, c) to val */
void image_setz(Image *src, int r, int c, float val) {
if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at image_setz\n");
    return;
  }
  src->data[r*src->cols + c].z = val;  
}

/* resets every pixel to a default value (e.g. Black, alpha value of 1.0, z value of 1.0). */
void image_reset(Image *src) {
  int i, j;
  for (i=0; i<src->rows; i++) {
    for (j=0; j<src->cols; j++) {
      src->data[i*src->cols + j].rgb[0] = 0.0;
      src->data[i*src->cols + j].rgb[1] = 0.0;
      src->data[i*src->cols + j].rgb[2] = 0.0;
      src->data[i*src->cols + j].a = 1.0;
      src->data[i*src->cols + j].z = 1.0;
    }
  }
}

/* sets every FPixel to the given value */
void image_fill(Image *src, FPixel val) {
  int i, j;
  for (i=0; i<src->rows; i++) {
    for (j=0; j<src->cols; j++) {
      src->data[i*src->cols + j] = val;
    }
  }
}

/* sets the (r, g, b) values of each pixel to the given color */
void image_fillrgb(Image *src, float r, float g, float b) {
  int i, j;
  for (i=0; i<src->rows; i++) {
    for (j=0; j<src->cols; j++) {
      src->data[i*src->cols + j].rgb[0] = r;
      src->data[i*src->cols + j].rgb[1] = g;
      src->data[i*src->cols + j].rgb[2] = b;      
    }
  }
}

/* sets the alpha value of each pixel to the given value */
void image_filla(Image *src, float a) {
  int i, j;
  for (i=0; i<src->rows; i++) {
    for (j=0; j<src->cols; j++) {
      src->data[i*src->cols + j].a = a; 
    }
  }
}

/* sets the z value of each pixel to the given value */
void image_fillz(Image *src, float z) {
  int i, j;
  for (i=0; i<src->rows; i++) {
    for (j=0; j<src->cols; j++) {
      src->data[i*src->cols + j].z = z; 
    }
  }
}



