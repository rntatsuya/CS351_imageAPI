/**
 * Kimberly Required Image 3
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

void addLayer( Module *mod, int num, int dx );
void addLayer( Module *mod, int num, int dx ) {
	for ( int i = 0; i < num; i++ ) {
		module_translate( mod, dx, 0.0, 0.0 );
		cube( mod );
	}	
}

int main( int argc, char *argv[] ) {
	Image *src;
	Module *scene;
	Module *legs;
	Module *table;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Point pt[8];
  	srand48(42);
  	Color *Random;

	int angle = 7;

	if (argc <= 1) {
		printf("Please specify number between 1 and 7 inclusive\n");
		exit(-1);
	} 

	angle = atoi(argv[1]);

	if ((angle < 1) || (angle > 7)) {
		printf("Please specify number between 1 and 7 inclusive\n");
		exit(-1);
	}
	
	switch(angle) {
		case 1: // From positive Z looking in
			{
			printf("PERSPECTIVE 1\n");
			point_set3D( &(view.vrp), 0, 0, 100 );
			vector_set( &(view.vpn), 0, 0, -100 );
			vector_set( &(view.vup), 0, 1, 0 ); 
			break;
			} 
		case 2: // From negative Z looking in 
			{
			printf("PERSPECTIVE 2\n");
			point_set3D( &(view.vrp), 0, 0, -100 );
			vector_set( &(view.vpn), 0, 0, 100 );
			vector_set( &(view.vup), 0, 1, 0 );
			break;
			} 
		case 3: // From positive Y looking in 
		  	{
			printf("PERSPECTIVE 3\n");
		  	point_set3D( &(view.vrp), 0, 100, 0 );
			vector_set( &(view.vpn),  0, -100, 0 );
			vector_set( &(view.vup), 0, 0, 1 );
			break;
			}
		case 4: // From negative Y looking in 
			{
			printf("PERSPECTIVE 4\n");
		  	point_set3D( &(view.vrp), 0, -100, 0 );
			vector_set( &(view.vpn),  0, 100, 0 );
			vector_set( &(view.vup), 0, 0, 1 );
			break;
			}
		case 5: // From positive X looking in 
		  	{
			printf("PERSPECTIVE 5\n");
		  	point_set3D( &(view.vrp), 100, 0, 0 );
			vector_set( &(view.vpn), -100, 0, 0 );
			vector_set( &(view.vup), 0, 0, 1 );
			break;
			}
		case 6: // From negative X looking in 
		  	{
			printf("PERSPECTIVE 6\n");
		  	point_set3D( &(view.vrp), -100, 0, 0 );
			vector_set( &(view.vpn), 100, 0, 0 );
			vector_set( &(view.vup), 0, 0, 1 );
			break;
			}
		case 7: // Bruce's coordinate
			{
			printf("PERSPECTIVE 7\n");
		  	point_set3D( &(view.vrp), 15, 30, 100 );
			vector_set( &(view.vpn), -20, -30, -100 );
			vector_set( &(view.vup), 0, 1, 0 );
			break;
			}
	}
  
	view.d = 2.2;
	view.du = 1.6;
	view.dv = 0.9;
	view.f = 1;
	view.b = 50;
	view.screenx = 640;
	view.screeny = 360;

	matrix_setView3D( &vtm, &view );
	matrix_identity( &gtm );

	// Create 4 legs of table
	legs = module_create(); 
	module_rotateZ( legs, cos( 1 ), sin( 0 ) );
	module_scale( legs, 3.0, 3.0, 3.0 );
	build( legs );	
	module_translate( legs, 9, 0, 0 ); 
	build( legs );
	module_translate( legs, 0, 9, 0 ); 
	build( legs );
	module_translate( legs, -9, 0, 0 ); 
	build( legs );

	// Create table 
	table = module_create(); 
	module_module( table, legs );
	module_scale(table, 10.0, 10.0, 1.0);
	module_translate( table, 5, 5, 1 ); 
	cube( table);

	// Add multiple tables to scene
	scene = module_create();
 //  	color_set( &Random, 1.0, drand48(), drand48() );
	// module_color( scene, &Random ); 
  	module_rotateZ( scene, cos( 0.87 ), sin(0.50) ); 
	module_module( scene, table );
	
	// color_set( &Random, drand48(), 1.0, drand48() );
	// module_color( scene, &Random ); 
	module_scale(scene, 0.5, 0.75, 0.5);
	// Make function for rotating with degree value as input
  	module_rotateX( scene, cos( 0.90), sin(0.17) ); 
	module_translate( scene, -25, -5, 7 ); 
	module_module( scene, table );
	
	// color_set( &Random, drand48(), drand48(), 1.0 );
	// module_color( scene, &Random ); 
	module_scale(scene, 1.5, 1.75, 1.0);
  	module_rotateX( scene, cos( 0.87), sin(0.50) ); 
	module_translate( scene, 60, 0, 10 ); 
	module_module( scene, table );
	
	// color_set( &Random, 1.0, drand48(), drand48() );
	// module_color( scene, &Random ); 
	module_scale(scene, 0.5, 0.20, 0.75);
	module_translate( scene, -30, 0, -20 ); 
	module_module( scene, table );
	
	// Create image
	src = image_create( 360, 640, 255 );
	ds = drawstate_create();
	ds->shade = ShadeFrame;

	// draw into the scene
	module_draw( scene, &vtm, &gtm, ds, NULL, src );
	
	// write out the scene
	image_write( src, "tables.ppm" );
	
	// free the polygon data
	polygon_clear( &p );

	// free the modules
	module_delete( scene );
	module_delete( legs );

	// free the drawstate
	free(ds);

	// free the image
	image_free( src );

	return(0);	
}