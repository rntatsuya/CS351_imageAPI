/*
  Bruce A. Maxwell
  Fall 2014

  Example code for drawing a single cube

  C Version
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  Image *src;
  Matrix VTM;
  Matrix GTM;
  Module *cube;
  int rows = 360;
  int cols = 640;

  Color Grey = {{0.6, 0.62, 0.64}};

  DrawState *ds;
  View3D view;

  // initialize the image
  src = image_create(rows, cols, 255);

  // initialize matrices
  matrix_identity(&GTM);
  matrix_identity(&VTM);

  // set the View parameters
  point_set3D(&(view.vrp), 5, 5, -7.0);
  vector_set(&(view.vpn), -5, -5, 7);
  vector_set(&(view.vup), 0.0, 1.0, 0.0);
  view.d = 2.0;
  view.du = 1.6;
  view.dv = .9;
  view.f = 0.0;
  view.b = 15;
  view.screenx = cols;
  view.screeny = rows;
  matrix_setView3D(&VTM, &view);

  // print out VTM
  printf("Final VTM: \n");
  matrix_print(&VTM, stdout);

  // make a simple cube module
  cube = module_create();
  module_scale( cube, 3, 1, 2 );
  module_color( cube, &Grey );
  module_cube( cube, 1);


  ds = drawstate_create();
  ds->shade = ShadeDepth;

  int i;
  for(i=0;i<36;i++) {
    char buffer[256];

    image_reset( src );

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    // module_draw(scene, &VTM, &GTM, ds, NULL, src);
    module_draw(cube, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "test8a-%03d.ppm", i);
    image_write(src, buffer);
  }

  // matrix_identity(&GTM);
  // module_draw(cube, &VTM, &GTM, ds, NULL, src);

  // write 
  // out the image
  // image_write(src, "test8a.ppm");

  // free stuff here
  module_delete( cube );
  image_free( src );
  

  return(0);
}