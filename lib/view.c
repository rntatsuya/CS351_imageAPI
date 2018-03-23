/**
 * Kimberly and Tatsuya
 * view.c
 */

#include "matrix.h"
#include "view.h"
#include <math.h>

void matrix_setView2D(Matrix *vtm, View2D *view) {
	int dx = view->dx;
	int screenx = view->screenx;
	int screeny = view->screeny;
	int dy = dx * screeny / screenx; // height of view window
	
	matrix_translate( vtm, -view->vrp.val[0], -view->vrp.val[1], 0 );
	matrix_rotateZ( vtm, view->x.val[0], -view->x.val[1] );
	matrix_scale( vtm, screenx/dx, -screeny/dy, 1 );
	matrix_translate( vtm, screenx/2, screeny/2, 0 );
}

// void matrix_setView3D( Matrix *vtm, View3D *view ) {
// 	
// }
