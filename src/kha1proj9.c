/**
 * Kimberly Required Image 1
 * Project 9 
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
  int i, j; 
  Color White;
  Color Grey;
	Color DkGrey;
	Color Blue;


  DrawState *ds;
  View3D view;

  Lighting *light;

	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Grey, 0.6, 0.62, 0.64 );
	color_set( &DkGrey, 0.1, 0.1, 0.1 );
	color_set( &Blue, 0, 0, 1.0 );


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
  module_scale( cube, 3, 3, 3 );
  module_color( cube, &White );
  module_bodyColor( cube, &White );
  module_surfaceColor( cube, &DkGrey );
  module_cube( cube, 1);

	// Window
	module_color( cube, &Blue );

	for ( i = 0; i < 2; i++ ) {
		for ( j = 0; j < 2; j++ ) {
			module_identity( cube );
			module_scale( cube, 0.7, 1, 0.20 );
			module_bodyColor( cube, &Blue );
			module_surfaceColor( cube, &DkGrey );
			module_translate( cube, -1.2+(1.5*i), -0.2+(j*1.2), 2 );
			module_cube( cube, 1);

			module_identity( cube );
			module_scale( cube, 0.20, 1, 0.70 );
			module_bodyColor( cube, &Blue );
			module_surfaceColor( cube, &DkGrey );
			module_translate( cube, -2, -0.2+(i*1.2), 0.2+(1.2*j)  );
			module_cube( cube, 1);
		}
	}

	module_identity( cube );
	module_scale( cube, 0.4, 1.0, 0.15 );
	module_bodyColor( cube, &Blue );
	module_surfaceColor( cube, &White );
	module_translate( cube, -0.4, -0.5, 2 );
	module_cube( cube, 1);

  // manually add a light source to the Lighting structure
  // put it in the same place as the eye in world space
  light = lighting_create();
  lighting_add( light, LightPoint, &White, NULL, &(view.vrp), 0, 0 );
  lighting_add( light, LightPoint, &White, NULL, &(view.vrp), -8, 0 );

  // set the shading to Gouraud
  ds = drawstate_create();
	
  point_copy(&(ds->viewer), &(view.vrp));
	ds->shade = ShadeGouraud;
	//	ds->shade = ShadeFlat;

  matrix_identity(&GTM);
  module_draw(cube, &VTM, &GTM, ds, light, src);

  // write out the image
  image_write(src, "kha9_1.ppm");

  // free stuff here
  module_delete( cube );

  image_free( src );
  

  return(0);
}
