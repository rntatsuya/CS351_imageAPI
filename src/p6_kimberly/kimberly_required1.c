/**
 * Kimberly Required Image 1
 * Project 6
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

// Creates leg of table of size 1x1x3
void build( Module *mod );
void build( Module *mod ) {
	Point pt[4];
	Polygon s;
	polygon_init ( &s );

	// Top face
	point_set3D( &pt[0], 0, 0, 0 );
	point_set3D( &pt[1], 0, -1, 0 );
	point_set3D( &pt[2], 1, -1, 0 );
	point_set3D( &pt[3], 1, 0, 0 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	// Bottom face
	point_set3D( &pt[0], 0, 0, -3 );
	point_set3D( &pt[1], 0, -1, -3 );
	point_set3D( &pt[2], 1, -1, -3 );
	point_set3D( &pt[3], 1, 0, -3 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	// Sides
	point_set3D( &pt[0], 0, 0, 0 );
	point_set3D( &pt[1], 1, 0, 0);
	point_set3D( &pt[2], 1, 0, -3 );
	point_set3D( &pt[3], 0, 0, -3 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	point_set3D( &pt[0], 1, 0, 0 );
	point_set3D( &pt[1], 1, -1, 0);
	point_set3D( &pt[2], 1, -1, -3 );
	point_set3D( &pt[3], 1, 0, -3 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	point_set3D( &pt[0], 1, -1, 0 );
	point_set3D( &pt[1], 0, -1, 0);
	point_set3D( &pt[2], 0, -1, -3 );
	point_set3D( &pt[3], 1, -1, -3 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	point_set3D( &pt[0], 0, -1, 0 );
	point_set3D( &pt[1], 0, 0, 0 );
	point_set3D( &pt[2], 0, 0, -3 );
	point_set3D( &pt[3], 0, -1, -3 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );

	// Single window 
	point_set3D( &pt[0], 0.25, 0, -2.0 );
	point_set3D( &pt[1], 0.25, 0, -1.5 );
	point_set3D( &pt[2], 0.75, 0, -1.5 );
	point_set3D( &pt[3], 0.75, 0, -2.0 );
	polygon_set( &s, 4, pt );
	module_polygon( mod, &s );
}

// adds a cube centered on the origin of width 2x2x2 to the module
void cube( Module *mod );
void cube( Module *mod ) {
  Point pt[4];
  Polygon p;

  polygon_init( &p );
  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1, -1,  1 );
  point_set3D( &pt[2], -1,  1,  1 );
  point_set3D( &pt[3], -1,  1, -1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

  point_set3D( &pt[0], 1, -1, -1 );
  point_set3D( &pt[1], 1, -1,  1 );
  point_set3D( &pt[2], 1,  1,  1 );
  point_set3D( &pt[3], 1,  1, -1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1, -1,  1 );
  point_set3D( &pt[2],  1, -1,  1 );
  point_set3D( &pt[3],  1, -1, -1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, 1, -1 );
  point_set3D( &pt[1], -1, 1,  1 );
  point_set3D( &pt[2],  1, 1,  1 );
  point_set3D( &pt[3],  1, 1, -1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1,  1, -1 );
  point_set3D( &pt[2],  1,  1, -1 );
  point_set3D( &pt[3],  1, -1, -1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, 1 );
  point_set3D( &pt[1], -1,  1, 1 );
  point_set3D( &pt[2],  1,  1, 1 );
  point_set3D( &pt[3],  1, -1, 1 );
  polygon_set( &p, 4, pt );
  module_polygon( mod, &p );

}

int main( int argc, char *argv[] ) {
	Image *src;
	Module *scene;
	Module *buildings;
	Module *city;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Point pt[8];
  	srand48(42);

	// set up the view
	point_set3D( &(view.vrp), 50, 50, 50 );
	vector_set( &(view.vpn), 20, 20, 20 );
	vector_set( &(view.vup), 0, 0, 1 );
	view.d = 2.2;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 50;
	view.screenx = 640;
	view.screeny = 360;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	// Create 4 building 
	buildings = module_create(); 
	module_rotateZ( buildings, cos( 1 ), sin( 0 ) );
	module_scale( buildings, 3.0, 3.0, 3.0 );
	build( buildings );	
	module_translate( buildings, 9, 0, 0 ); 
	build( buildings );
	module_translate( buildings, 0, 9, 0 ); 
	build( buildings );
	module_translate( buildings, -9, 0, 0 ); 
	build( buildings );

	// Create city 
	city = module_create(); 
	module_module( city, buildings );
	module_translate( city, -15.0, -20.0, 0.0 );
	module_module( city, buildings );
	module_scale( city, 0.74, 0.74, 0.74 );
	module_translate( city, -10.0, 20.0, 0.0 );
	module_module( city, buildings );

	// Add buildings to scene
	scene = module_create();
	module_module( scene, city );

	Color Random;
	
	// Draw stars into the scene
	module_identity(scene);
	for(int i=0;i<100;i++) {
		point_set3D( &(pt[0]), drand48()*10, drand48()*20,  drand48()*20 );
		color_set( &Random, drand48(), drand48(), drand48() );
		module_color( scene, &Random ); 
		module_point( scene, &(pt[0]) );
	}
	
	// Create image
	src = image_create( 360, 640, 255 );
	ds = drawstate_create();
	ds->shade = ShadeFrame;

	// draw into the scene
	module_draw( scene, &vtm, &gtm, ds, NULL, src );
	
	// write out the scene
	image_write( src, "city.ppm" );
	
	// free the polygon data
	polygon_clear( &p );

	// free the modules
	module_delete( scene );
	module_delete( buildings );

	// free the drawstate
	free(ds);

	// free the image
	image_free( src );

	return(0);	
}