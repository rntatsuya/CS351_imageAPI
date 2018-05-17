/**
 * Kimberly Required Image 1
 * Project 8
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
  Module *cube, *scene;
  int rows = 360;
  int cols = 640;

  Color Neon = {{0.0, 1.0, 1.0}};
  Color White = {{1.0, 1.0, 1.0}};

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
  module_color( cube, &Neon );
  module_cube( cube, 1 );

  scene = module_create();
  module_module( scene, cube );
  
  module_identity( scene );
  module_scale( scene, 2, 2, 2 );
  module_translate( scene, 1.5, 1.5, 0 );
  module_module( scene, cube );

  module_identity( scene );
  module_scale( scene, 0.5, 0.5, 0.5 );
  module_translate( scene, 3.0, 3.0, 0 );
  module_module( scene, cube );

  module_identity( scene );
  module_scale( scene, 3, 3, 3 );
  module_translate( scene, 0, -2, -2 );
  module_module( scene, cube );

  ds = drawstate_create();
  ds->shade = ShadeDepth;

  int i;
  for(i=0;i<36;i++) {
    char buffer[256];

    image_reset( src );

    matrix_identity(&GTM);

    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    matrix_rotateX(&GTM, cos(i*4*M_PI/36.0), sin(i*4*M_PI/36.0));
    matrix_rotateZ(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));

    module_draw(scene, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "kha1proj8-%03d.ppm", i);
    image_write(src, buffer);
  }

  // free stuff here
  module_delete( cube );
  image_free( src );
  

  return(0);
}