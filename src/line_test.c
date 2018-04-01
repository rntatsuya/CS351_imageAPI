/*
  Bruce Maxwell
  Fall 2014

  2D View test function
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"


int main(int argc, char *argv[]) {
  const int rows = 180;
  const int cols = 320;
  Line line;
  Color color;
  char filename[256];
  Image *src;

  src = image_create( rows, cols, 255 );

  line_set2D( &line, -64.91, 33.28 ,51.35, 87.52 );
  color_set( &color, 1.0, 1.0, 1.0 );
  line_draw( &line, src, color );




  printf("writing file\n");
  sprintf(filename, "line_test.ppm" );
  image_write( src, filename );

  
  printf("Cleaning up\n");
  // cleanup
  image_free( src );

  return(0);
}
