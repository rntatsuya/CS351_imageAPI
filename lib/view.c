/**
 * Kimberly and Tatsuya
 * view.c
 */

#include "matrix.h"
#include "view.h"
#include <math.h>

void matrix_setView2D( Matrix *vtm, View2D *view ) {
	printf("matrix_setView2D\n");
	double du = view->dx;
	double c = view->screenx;
	double r = view->screeny;
	double dv = du * r / c; // height of view window

	matrix_translate2D( vtm, -view->vrp.val[0], -view->vrp.val[1] );
	matrix_rotateZ( vtm, view->x.val[0], -view->x.val[1] );
	matrix_scale2D( vtm, c/du, -r/dv );
	matrix_translate2D( vtm, c/2.0, r/2.0 );

	// matrix_translate( vtm, -view->vrp.val[0], -view->vrp.val[1], 0.0 );
	// matrix_rotateZ( vtm, view->x.val[0], -view->x.val[1] );
	// matrix_scale( vtm, screenx/dx, -screeny/dy, 1.0 );
	// matrix_translate( vtm, screenx/2.0, screeny/2.0, 0.0 );
}

void matrix_setView3D( Matrix *vtm, View3D *view ) {
	
}
