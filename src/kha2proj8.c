/**
 * Kimberly Required Image 2
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
  Module *sun, *earth, *mercury, *venus, *mars, *jupiter, *saturn, *neptune, *uranus, *pluto;
  int rows = 600;
  int cols = 1000;

  Color Grey = {{0.6, 0.62, 0.64}};
  Color Yellow = {{1.0, 1.0, 0.0}};
  Color Brown = {{102/255.0, 51/255.0, 0/255.0}};
  Color Blue = {{0/255.0, 102/255.0, 204/255.0}};

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

  // make a simple sun
  sun = module_create();
  module_scale( sun, 1, 1, 1 );
  module_color( sun, &Yellow );
  module_sphere( sun, 3 );

  mercury = module_create(); 
  module_scale( mercury, 0.5, 0.5, 0.5 );
  module_translate( mercury, 2, 0, 0 ); 
  module_color( mercury, &Brown );
  module_sphere( mercury, 5 );

  venus = module_create();
  module_scale( venus, 0.75, 0.75, 0.75 );
  module_translate( venus, 3, 0, 0 ); 
  module_color( venus, &Brown );
  module_sphere( venus, 4 );

  earth = module_create(); 
  module_scale( earth, 1.5, 1.5, 1.5 );
  module_translate( earth, 6, 0, 0 ); 
  module_color( earth, &Blue );
  module_sphere( earth, 4 );

  // mars = module_create(); 
  // module_scale( mars, 1/208.0, 1/208.0, 1/208.0 );
  // module_translate( mars, 3, 0, 0 ); 
  // module_color( mars, &Brown );
  // module_sphere( mars, 4 );

  // jupiter = module_create(); 
  // module_scale( jupiter, 1/9.68, 1/9.68, 1/9.68 );
  // module_translate( jupiter, 3, 0, 0 ); 
  // module_color( jupiter, &Brown );
  // module_sphere( jupiter, 4 );

  // saturn = module_create(); 
  // module_scale( pluto, 1/11.4, 1/11.4, 1/11.4 );
  // module_translate( saturn, 3, 0, 0 ); 
  // module_color( saturn, &Brown );
  // module_sphere( saturn, 4 );

  // uranus = module_create(); 
  // module_scale( uranus, 1/26.8, 1/26.8, 1/26.8 );
  // module_translate( uranus, 3, 0, 0 ); 
  // module_color( uranus, &Brown );
  // module_sphere( uranus, 4 );

  // neptune = module_create(); 
  // module_scale( neptune, 1/27.7, 1/27.7, 1/27.7 );
  // module_translate( neptune, 3, 0, 0 ); 
  // module_color( neptune, &Brown );
  // module_sphere( neptune, 4 );

  // pluto = module_create(); 
  // module_scale( pluto, 1/11.4, 1/11.4, 1/11.4 );
  // module_translate( pluto, 3, 0, 0 ); 
  // module_color( pluto, &Brown );
  // module_sphere( pluto, 4 );

  ds = drawstate_create();
  ds->shade = ShadeDepth;

  int i;
  for(i=0;i<36;i++) {
    char buffer[256];

    image_reset( src );

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    module_draw(sun, &VTM, &GTM, ds, NULL, src);

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*4*M_PI/36.0), sin(i*4*M_PI/36.0));
    module_draw(mercury, &VTM, &GTM, ds, NULL, src);

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*4*M_PI/36.0), sin(i*4*M_PI/36.0));
    module_draw(mercury, &VTM, &GTM, ds, NULL, src);

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    module_draw(earth, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "kha2proj8-%03d.ppm", i);
    image_write(src, buffer);
  }

  // free stuff here
  module_delete( earth );
  module_delete( mercury );
  module_delete( sun );
  image_free( src );
  
  printf("Done with kha2proj8\n");

  return(0);
}