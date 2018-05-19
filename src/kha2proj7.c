/**
 * Kimberly Required Image 2
 * Project 7 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"
#include <time.h>

void cylinder( Module *mod, int sides );
void cylinder( Module *mod, int sides ) {
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
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

    polygon_set( &p, 3, pt );
    module_polygon( mod, &p );

    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    module_polygon( mod, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );
    
    polygon_set( &p, 4, pt );
    module_polygon( mod, &p );
  }

  polygon_clear( &p );
}

int main(int argc, char *argv[]) {
	int frame;
	Color blue, green, purple, red, white, blue2;
	Point p[16];
	BezierSurface bc;
	DrawState ds;
	Module *curve, *scene;
	View3D view;
	Matrix VTM, GTM;
	int divisions = 4;
	int rows = 600, cols = 1000;
	Image *src = image_create(rows, cols, 255);
	srand48(0x01234ABCD);

	// srand((unsigned) time(&t));

	// grab the command line argument, if one exists
	if(argc > 1) {
		int tmp = atoi(argv[1]);
		if( tmp >= 0 && tmp < 10 )
			divisions = tmp;
	}
	printf("Creating Bezier curves with %d subdivisions\n", divisions);

	color_set(&white, 1.0, 1.0, 1.0 );
	color_set(&blue, .1, .2, .8);
	color_set(&blue2, .1, .1, .4);
	color_set(&green, .2, 0.7, 0.3 );
	color_set(&purple, 0.6, 0.1, 0.7 );
	color_set(&red, 0.75, 0.3, 0.3 );

	curve = module_create();

	printf("Starting new surface!\n");

	// create a curved surface 
	for ( int q = 0; q < 16; q++ ) {
		point_set3D(&p[q], q/4, (-5)*drand48(), q%4); 
	}

	bezierSurface_set(&bc, p);

	// put the curve into a module
	module_color(curve, &green);
	module_translate( curve, 0, 2, 0);
	module_bezierSurface(curve, &bc, divisions, 0);

	scene = module_create(); 
	module_module( scene, curve );

	Point p1, p2;
	Line line; 
	// Create rain drops
	for ( int q = 0; q < 16; q++ ) {
		printf("line set %d\n", q);
		point_set3D( &p1, q%4-drand48()/5, 0.5-drand48()/3, q/4+drand48()/3 );
		point_set3D( &p2, q%4+drand48()/5, 0.6+drand48()/3, q/4-drand48()/3 );
		line_set3D( &line, p1, p2 );
		module_color(scene, &blue);
		module_line( scene, &line );

		point_set3D( &p1, q%4-drand48()/5, 0.1-drand48()/3, q/4+drand48()/3 );
		point_set3D( &p2, q%4+drand48()/5, 0.2+drand48()/3, q/4-drand48()/3 );
		line_set3D( &line, p1, p2 );
		module_color(scene, &blue2);
		module_line( scene, &line );

		point_set3D( &p1, q%4-drand48()/5, 0.4-drand48()/3, q/4+drand48()/3 );
		point_set3D( &p2, q%4+drand48()/5, 0.5+drand48()/3, q/4-drand48()/3 );
		line_set3D( &line, p1, p2 );
		module_color(scene, &blue);
		module_line( scene, &line );
	}

	for ( int i = 0; i < 20; i++ ) {
		module_identity( scene );
		module_color( scene, &white );
		module_scale( scene, 0.20, 0.20, 0.20 );
		module_rotateX( scene, 0.707, 0.707 );
		module_rotateZ( scene, 0.707, 0.707 );
		module_translate( scene, 0.5+drand48()*3, 1, 0.5+drand48()*3 );
		cylinder( scene, 10 );
	}
	
	// set up the drawstate
	drawstate_setColor(&ds, white);

	// set up the view
	point_set3D(&(view.vrp), 0.0, 4.8, -12.0 );
	vector_set( &(view.vpn), 0.0, -0.8, 2.5 );
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.5;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 3.0;

	matrix_setView3D( &VTM, &view );
	matrix_identity( &GTM );

	// Create the animation by adjusting the GTM
	for(frame=0;frame<60;frame++) {
		char buffer[256];
		printf("frame %d\n", frame);
		matrix_rotateY(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
		matrix_rotateX(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( scene, &VTM, &GTM, &ds, NULL, src );

		sprintf(buffer, "k2p7-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	// clean up
	image_free( src );

	module_delete( curve );

	return(0);
}