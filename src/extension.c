/**
 * Kimberly & Tatsuya Extension
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
	Module *chair;
	Module *chairs;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Point pt[8];
  	srand48(42);
  	Color White = { { 255.0/255.0, 204.0/255.0, 153.0/255.0 } };
  	Color Mid_Brown = { { 97.0/255.0, 3.0/255.0, 3.0/255.0 } };
  	Color Light_Brown = { { 102.0/255.0, 51.0/255.0, 0.0/255.0 } };
	Color Brown =  { { 0.0/255.0, 153.0/255.0, 153.0/255.0 } };
	Color Blue =  { { 51.0/255.0, 255.0/255.0, 255.0/255.0 } };
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
	module_color( legs, &White );
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

	// Single chair
	chair = module_create(); 
	module_color( chair, &White ); 				// Legs of chair
	module_module( chair, legs );

	module_color( chair, &Light_Brown ); 		// Seat cusion
	module_scale(chair, 10.0, 10.0, 1.0);
	module_translate( chair, 5, 5, 1 ); 
	cube( chair); 

	module_color( chair, &Mid_Brown ); 			// Back
	module_scale(chair, 0.2, 1, 5 );
	module_translate( chair, 10, 0, 0 ); 
	cube( chair);

	// Chairs
	chairs = module_create(); 
	module_color( chairs, &Blue );
	module_module( chairs, table ); // Adding table
	
	module_scale( chairs, 0.30, 0.30, 0.70); 	// Left chair
	module_translate( chairs, 21, 4, -3 ); 
	module_module( chairs, chair );
	
	module_translate( chairs, -35, 0, 0 ); 		// Right chair
	module_module( chairs, chair );
	
	module_translate( chairs, 17, -17, 0 ); 	// Bottom chair
	module_module( chairs, chair );
	
	module_translate( chairs, 0, 32, 0 ); 		// Top chair
	module_module( chairs, chair );

	// Add multiple tables to scene
	scene = module_create();
	// module_rotateZ( scene, cos( 0.90), sin(0.17) ); 
	// module_rotateX( scene, cos( 0.90), sin(0.17) ); 
	module_module( scene, chairs );
	
	// Create image
	src = image_create( 360, 640, 255 );
	ds = drawstate_create();
	ds->shade = ShadeFrame;

	// draw into the scene
	module_draw( scene, &vtm, &gtm, ds, NULL, src );
	
	// write out the scene
	image_write( src, "table_chairs.ppm" );
	
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