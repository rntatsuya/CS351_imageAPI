/**
 * Kimberly and Tatsuya
 * view.c
 */

#include "matrix.h"
#include "view.h"
#include <math.h>

void matrix_setView2D(Matrix *vtm, View2D *view) {
	double dx = view->dx;
	int screenx = view->screenx;
	int screeny = view->screeny;
	double dy = dx * screeny / screenx; // height of view window
	
	// need to initialize vtm to the identity
	matrix_identity( vtm );
	
	matrix_translate2D( vtm, -view->vrp.val[0], -view->vrp.val[1] );
	matrix_rotateZ( vtm, view->x.val[0], -view->x.val[1] );
	matrix_scale2D( vtm, screenx/dx, -screeny/dy );
	matrix_translate2D( vtm, screenx/2, screeny/2 );
}

void matrix_setView3D( Matrix *vtm, View3D *view ) {
	matrix_identity( vtm );
	
	// calculate u by taking cross product of vup and vpn
	Vector u;
	Vector vpn = view->vpn;
	Vector vup = view->vup;
	
	vector_cross( &vup, &vpn, &u );
	vector_cross( &vpn, &u, &vup );
	
	// normalize u, vup_dash, and vpn
	vector_normalize( &u );
	vector_normalize( &vup );
	vector_normalize( &vpn );
	
	double d = view->d;
	double B_dash = view->b + d;
	double d_dash = d/B_dash;
	double du = view->du;
	double dv = view->dv;
	int screenx = view->screenx;
	int screeny = view->screeny;	
	
	printf("original\n");
	matrix_print(vtm, stdout);
	matrix_translate( vtm, -view->vrp.val[0], -view->vrp.val[1], -view->vrp.val[2] );
	printf("translate\n");
	matrix_print(vtm, stdout);
	
	matrix_rotateXYZ( vtm, &u, &vup, &vpn );
	printf("rotate\n");
	matrix_print(vtm, stdout);
	
	matrix_translate( vtm, 0, 0, view->d );
	printf("translate\n");
	matrix_print(vtm, stdout);
	
	matrix_scale( vtm, 2*d/(B_dash*du), 2*d/(B_dash*dv), 1/B_dash );
	printf("scale\n");
	matrix_print(vtm, stdout);
	
	matrix_perspective( vtm, d_dash );
	printf("perspective\n");
	matrix_print(vtm, stdout);
		
	matrix_scale( vtm, -screenx/(2*d_dash), -screeny/(2*d_dash), 1 );
	printf("scale\n");
	matrix_print(vtm, stdout);
	
	matrix_translate( vtm, screenx/2, screeny/2, 0 );
	printf("translate\n");
	matrix_print(vtm, stdout);
}
