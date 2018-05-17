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
  Module *sun, *mars, *earth, *mercury, *venus;
  int rows = 600;
  int cols = 1000;

  Color Grey = {{0.6, 0.62, 0.64}};
  Color Yellow = {{1.0, 1.0, 0.0}};
  Color Brown = {{166/255.0, 100/255.0, 0/255.0}};
  Color Blue = {{0/255.0, 102/255.0, 240/255.0}};
  Color White = {{ 191/255.0, 191/255.0, 191/255.0}};
  Color Red = {{ 255.0/255.0, 0/255.0, 0/255.0}};

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
  module_sphere( mercury, 3 );

  venus = module_create();
  module_scale( venus, 0.4, 0.4, 0.4 );
  module_translate( venus, 4, 0, 0 ); 
  module_color( venus, &Grey );
  module_sphere( venus, 3 );

  earth = module_create(); 
  module_scale( earth, 0.8, 0.8, 0.8 );
  module_translate( earth, 6, 0, 0 ); 
  module_color( earth, &Blue );
  module_sphere( earth, 3 );

  mars = module_create(); 
  module_scale( mars, 0.25, 0.25, 0.25 );
  module_translate( mars, 3, 0, 0 ); 
  module_color( mars, &Blue );
  module_sphere( mars, 3 );

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
    matrix_rotateY(&GTM, cos(i*3*M_PI/36.0), sin(i*3*M_PI/36.0));
    module_draw(venus, &VTM, &GTM, ds, NULL, src);

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    module_draw(earth, &VTM, &GTM, ds, NULL, src);

    matrix_identity(&GTM);
    matrix_rotateY(&GTM, cos(i*2*M_PI/36.0), sin(i*2*M_PI/36.0));
    module_draw(mars, &VTM, &GTM, ds, NULL, src);

    // write out the image
    sprintf(buffer, "kha2proj8-%03d.ppm", i);
    image_write(src, buffer);
  }

  // free stuff here
  module_delete( sun );
  module_delete( mercury );
  module_delete( venus );
  module_delete( earth );
  image_free( src );
  
  printf("Done with kha2proj8\n");

  return(0);
}