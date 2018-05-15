#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
	int i, frame;
	Color white;
	DrawState ds;
	Module *c;
	View3D view;
	Matrix VTM, GTM;
	
	int divisions = 4;
	int rows = 300, cols = 400;
	Image *src = image_create(rows, cols, 255);

	// grab the command line argument, if one exists
	if(argc > 1) {
		int tmp = atoi(argv[1]);
		if( tmp >= 0 && tmp < 20 )
			divisions = tmp;
	}
	
	printf("Creating cylinder with %d subdivisions\n", divisions);

	color_set(&white, 1.0, 1.0, 1.0 );
	c = module_create();
	module_cylinder( c, divisions );

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
		module_draw( c, &VTM, &GTM, &ds, NULL, src );
		sprintf(buffer, "0cylinder3d-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}

	// clean up
	image_free( src );
	module_delete( c );

	return(0);
}