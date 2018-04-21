/**
 * Kimberly Required Image 2
 * Project 6
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

/*
  Adds to the module a unit cylinder, aligned along the Y-axis

  Takes in the number of subdivisions to use when creating the cylinder
 */
void cylinder( Module *mod, int sides );

void cylinder( Module *mod, int sides ) {
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
  printf("init-ed\n");
  point_set3D( &xtop, 0, 1.0, 0.0 );
  point_set3D( &xbot, 0, 0.0, 0.0 );

  // make a fan for the top and bottom sides
  // and quadrilaterals for the sides
  for(i=0;i<sides;i++) {
    Point pt[4];

    x1 = cos( i * M_PI * 2.0 / sides );
    z1 = sin( i * M_PI * 2.0 / sides );
    x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
    z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

    point_copy( &pt[0], &xtop );
    point_set3D( &pt[1], x1, 1.0, z1 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    
    printf("here?\n");
    
    polygon_set( &p, 3, pt );
    printf("lplp\n");
    module_polygon( mod, &p );
    
    printf("here!\n");
    
    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    module_polygon( mod, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );
    
    printf("%d\n",i);
    
    polygon_set( &p, 4, pt );
    module_polygon( mod, &p );
  }

  polygon_clear( &p );
  printf("cleared\n");
}

// Adds a cube centered on the origin of width 2x2x2 to the module
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

// Resuse Bruce's Code
void clouds( Module *mod, int sides );
void clouds( Module *mod, int sides ) {
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
  printf("init-ed\n");
  point_set3D( &xtop, 0, 1.0, 0.0 );
  point_set3D( &xbot, 0, 0.0, 0.0 );

  // make a fan for the top and bottom sides
  // and quadrilaterals for the sides
  for(i=0;i<sides;i++) {
    Point pt[4];

    x1 = cos( i * M_PI * 2.0 / sides );
    z1 = sin( i * M_PI * 2.0 / sides );
    x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
    z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

    point_copy( &pt[0], &xtop );
    point_set3D( &pt[1], x1, 1.0, z1 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    
    printf("here?\n");
    
    polygon_set( &p, 3, pt );
    printf("lplp\n");
    module_polygon( mod, &p );
    
    printf("here!\n");
    
    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    module_polygon( mod, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );
    
    printf("%d\n",i);
    
    polygon_set( &p, 4, pt );
    module_polygon( mod, &p );
  }

  polygon_clear( &p );
  printf("cleared\n");
}

int main(int argc, char *argv[]) {

	Image *src;
	Module *scene;
	Module *base;
	Module *mountains;
	Module *air;
	Polygon p;
	View3D view;
	Matrix vtm, gtm;
	DrawState *ds;
	Color Forrest = { { 0.0, 102.0/255.0, 0.0 } };
	Color Sun = { { 255.0/255.0, 255.0/255.0, 53.0/255.0 } };
	Color Blue = { { 0.0/255.0, 128.0/255.0, 255.0/255.0 } };
	Color White =  { { 204.0/255.0, 1.0, 1.0 } };
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

	//////////////
	// Mountain //
	//////////////
	base = module_create();
	module_color( base, &Forrest );
	module_translate( base, 0, 0, -4 );
	module_scale( base, 2.0, 2.0, 2.0);
	addLayer( base, 5, 4.0 );
	module_translate( base, -14, 0.0, 4.0 );
	cube( base );
	addLayer( base, 3, 4.0 );
	module_translate( base, -10, 0.0, 4.0 );
	cube( base );
	addLayer( base, 2, 4.0 );	
	module_translate( base, -6, 0.0, 4.0 );
	cube( base );
	module_translate( base, 4.0, 0.0, 0.0 );
	cube( base );
	module_translate( base, -2, 0.0, 4.0 );
	module_color( base, &White );
	cube( base );

	///////////////////////
	// Mountainous Range //
	///////////////////////
	mountains = module_create();
	module_module( mountains, base );
	module_scale( mountains, 1.5, 1.5, 1.5 );
	module_translate( mountains, -40, 10.0, 0.0);
	module_module( mountains, base );
	module_scale( mountains, 0.30, 0.30, 0.30 );
	module_translate( mountains, 0.0, -10.0, 0.0);
	module_module( mountains, base );

	//////////////////
	// Clouds + Sun //
	//////////////////
  	air = module_create();
	module_module( air, mountains ); 		// Left clouds
	module_color( air, &Blue );
  	module_scale( air, 3, 3, 3 ); 
  	module_translate( air, -20, 0, 20);
  	clouds( air, 6 ); 
  	module_translate( air, -4, 0, -3);
  	clouds( air, 6 ); 
  	module_translate( air, -4, 0, 3);
  	clouds( air, 6 ); 
  	module_translate( air, -5, 0, -5);
  	clouds( air, 6 ); 

  	module_translate( air, 60, -10, 0); 	// Middle clouds
  	clouds( air, 6 ); 
  	module_translate( air, -4, 0, -3);
  	clouds( air, 6 ); 
  	module_translate( air, -5, 0, 5);
  	clouds( air, 6 ); 

	module_color( air, &Sun );				// Sun 
  	module_scale( air, 1.5, 1.5, 1.5 );
  	module_rotateX( air, cos( 0.87), sin(0.50) ); 
  	module_rotateZ( air, cos( 0.87), sin(0.50) ); 
  	module_translate( air, -25, 1, 5);
  	clouds( air, 6 ); 

	/////////////////
	// Main Scene  //
	/////////////////
	scene = module_create();
	module_module( scene, air );

	// create the image and drawstate
	src = image_create( 360, 640, 255 );
	ds = drawstate_create();
	ds->shade = ShadeFrame;

	// draw into the scene
	module_draw( scene, &vtm, &gtm, ds, NULL, src );

	// write out the scene
	image_write( src, "mountains.ppm" );

	// free the polygon data
	polygon_clear( &p );

	// free the modules
	module_delete( scene );
	module_delete( base );
	module_delete( mountains );
	module_delete( air );

	// free the drawstate
	free(ds);

	// free the image
	image_free( src );

	return(0);
}