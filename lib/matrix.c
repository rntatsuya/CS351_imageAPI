/**
 * Kimberly and Tatsuya
 * matrix.c
 */

#include "graphics.h"

//////////////////////////////
// Generic Matrix Functions //
//////////////////////////////
 
void matrix_print( Matrix *m, FILE *fp ) {

}

void matrix_clear( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			m->m[i * 4 + j] = 0.0;
}

void matrix_identity( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j )
				m->m[i * 4 + j] = 1.0;
 			else
				m->m[i * 4 + j] = 0.0;
		}
	}
}

double matrix_get( Matrix *m, int r, int c ) {
	return m->m[r * 4 + c];
}

void matrix_set( Matrix *m, int r, int c, double v ) {
	m->m[r * 4 + c] = v; 
}

void matrix_copy( Matrix *dest, Matrix *src ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			dest->m[i * 4 + j] = src->m[i * 4 + j];
}

// Not sure if this is correct 
void matrix_transpose( Matrix *m ) {
	// Matrix b; // Temp matrix

	// for ( int i = 0; i < 4; i++ )
 //        for ( int j = 0; j < 4; j++ ) 
 //            b->m[i * 4 + j] = m->m[j * 4 + i];

 //    for ( int i = 0; i < 4; i++ )
 //        for ( int j = 0; j < 4; j++ ) 
 //            m->m[i * 4 + j] = b->m[j * 4 + i];
}

void matrix_multiply( Matrix *left, Matrix *right, Matrix *m ) {
	for ( int i = 0; i < 4; i++) {
        for ( int j = 0; j < 4; j++ ) {
        	int d = i * 4 + j;
 	        m->m[d] = left->m[d] * right->m[d];
 	    }
 	}
}

void matrix_xformPoint( Matrix *m, Point *p, Point *q ) {
	for ( int i = 0; i < 4; i+=4 ) 
		q->val[i] = m->m[i]*p->val[0] 
			+ m->m[i+1]*p->val[1] 
			+ m->m[i+2]*p->val[2] 
			+ m->m[i+3]*p->val[3];
}

void matrix_xformVector( Matrix *m, Vector *p, Vector *q ) {
	for ( int i = 0; i < 4; i+=4 ) 
		q->val[i] = m->m[i]*p->val[0] 
			+ m->m[i+1]*p->val[1] 
			+ m->m[i+2]*p->val[2] 
			+ m->m[i+3]*p->val[3];
}

void matrix_xformPolygon( Matrix *m, Polygon *p ) {

}

void matrix_xformPolyline( Matrix *m, Polyline *p ) {

}

void matrix_xformLine( Matrix *m, Line *line ) {

}

/////////////////////////
// 2D Matrix Functions //
/////////////////////////

void matrix_scale2D( Matrix *m, double sx, double sy ) {

}

void matrix_rotateZ( Matrix *m, double cth, double sth ) {

}

void matrix_translate2D( Matrix *m, double tx, double ty ) {

}

void matrix_shear2D( Matrix *m, double shx, double shy ) {

}


/////////////////////////
// 3D Matrix functions //
/////////////////////////

void matrix_translate( Matrix *m, double tx, double ty, double tz ) {

}

void matrix_scale( Matrix *m, double sx, double sy, double sz ) {

}

void matrix_rotateX( Matrix *m, double cth, double sth ) {

}

void matrix_rotateY( Matrix *m, double cth, double sth ) {

}

void matrix_rotateXYZ( Matrix *m, Vector *u, Vector *v, Vector *w ) {

}

void matrix_shearZ( Matrix *m, double shx, double shy ) {

}

void matrix_perspective( Matrix *m, double d ) {

}
