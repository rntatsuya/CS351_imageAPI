/**
 * Kimberly Required Image 1
 * Project 7 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
	int i, frame;
	Color blue, green, purple, red, white;
	Point p[4];
	BezierCurve bc;
	BezierCurve;
	DrawState ds;
	Module *curveA;
	Module *scene;
	Module *flower;
	View3D view;
	Matrix VTM, GTM;
	int divisions = 4;
	int rows = 600, cols = 1000;
	Image *src = image_create(rows, cols, 255);

	// grab the command line argument, if one exists
	if(argc > 1) {
		int tmp = atoi(argv[1]);
		if( tmp >= 0 && tmp < 10 )
			divisions = tmp;
	}
	printf("Creating Bezier flower with %d subdivisions\n", divisions);

	color_set(&white, 1.0, 1.0, 1.0 );
	color_set(&blue, 0/255.0, 204/255.0, 255/255.0);
	color_set(&green, .2, 0.7, 0.3 );
	color_set(&purple, 0.6, 0.1, 0.7 );
	color_set(&red, 0.75, 0.3, 0.3 );

	// set one curve
	point_set3D(&p[0], 0.0, 0.0, 0.0);
	point_set3D(&p[1], -.2, 1, 0.0);
	point_set3D(&p[2], 0.4, 1, 0.0);
	point_set3D(&p[3], 0.2, 0.0, 0.0);
	bezierCurve_set(&bc, p);

	// put the curve into a module
	curveA = module_create();
	module_bezierCurve(curveA, &bc, divisions);
	module_rotateZ( curveA, 0, 1 );
	module_bezierCurve(curveA, &bc, divisions);
	module_rotateZ( curveA, 0, 1 );
	module_bezierCurve(curveA, &bc, divisions);
	module_rotateZ( curveA, 0, 1 );
	module_bezierCurve(curveA, &bc, divisions);
	
	flower = module_create();
	module_color(flower, &blue);
	module_module(flower, curveA);

	module_rotateZ( flower, 0.707, 0.707 );
	module_rotateX( flower, 0.707, 0.707 );
	module_color(flower, &white);
	module_module(flower, curveA);

	module_rotateX( flower, 0.707, 0.707 );
	module_color(flower, &blue);
	module_module(flower, curveA);

	module_rotateX( flower, 0.707, 0.707 );
	module_color(flower, &white);
	module_module(flower, curveA);

	scene = module_create(); 
	module_module(scene, flower);
	module_translate(scene, 1, 1, 0.0);
	module_module(scene, flower);
	module_identity(scene);
	module_translate(scene, 1, 0, 1.0);
	module_module(scene, flower);
	module_translate(scene, 1, 1, 1);
	module_module(scene, flower);
	module_identity(scene);
	module_translate(scene, -1, -1, -1);
	module_module(scene, flower);
	module_identity(scene);
	module_translate(scene, 1, -1, -1);
	module_module(scene, flower);

	// set up the drawstate
	drawstate_setColor(&ds, white);

	// set up the view
	point_set3D(&(view.vrp), 0.0, 0.5, -3.0 );
	vector_set( &(view.vpn), 0.0, 0.0, 1.0 );
	vector_set( &(view.vup), 0.0, 1.0, 0.0 );
	view.d = 1.0;
	view.du = 1.0;
	view.dv = 1.0*rows/cols;
	view.screeny = rows;
	view.screenx = cols;
	view.f = 0.0;
	view.b = 3.0;

	matrix_setView3D( &VTM, &view );
	matrix_identity( &GTM );

	printf("Creating Animation\n");
	// Create the animation by adjusting the GTM
	for(frame=0;frame<60;frame++) {
		char buffer[256];
		matrix_rotateY(&GTM, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( scene, &VTM, &GTM, &ds, NULL, src );
		sprintf(buffer, "kha1-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	// clean up
	image_free( src );

	module_delete( curveA );
	module_delete( scene );
	module_delete( flower );

	return(0);
}