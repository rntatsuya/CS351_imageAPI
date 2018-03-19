/**
 * Kimberly and Tatsuya
 * view.c
 */

#include "graphics.h"

void matrix_setView2D(Matrix *vtm, View2D *view) {
	int du = view->du;
	int c = view->c;
	int r = view->r;
	int dv = du * r / c; // height of view window
	int theta = view->theta;
	
	matrix_translate( vtm, -view->v0.val[0], -view->v0.val[1], 0 );
	matrix_rotateZ( vtm, theta, -theta );
	matrix_scale( vtm, c/du, -r/dv, 1 );
	matrix_translate( vtm, c/2, r/2, 0 );
}

// void matrix_setView3D( Matrix *vtm, View3D *view ) {
// 	
// }
