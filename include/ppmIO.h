#ifndef PPMIO_H

#define PPMIO_H

// probably using unsigned char because the value range is 0 to 255
typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

// PPM is a full-color image file, encoded with 3 bytes (24 bits) per pixel, 
// 1 byte per color
Pixel *readPPM(int *rows, int *cols, int * colors, char *filename);
void writePPM(Pixel *image, int rows, int cols, int colors, char *filename);

// PGM is a greyscale image file, encoded with 1 or 2 bytes per pixel
unsigned char *readPGM(int *rows, int *cols, int *intensities, char *filename);
void writePGM(unsigned char *image, long rows, long cols, int intensities, char *filename);


#endif
