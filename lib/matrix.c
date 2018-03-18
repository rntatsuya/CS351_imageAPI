/**
 * Kimberly and Tatsuya
 * matrix.c
 */

#include "matrix.h"

//////////////////////////////
// Generic Matrix Functions //
//////////////////////////////
 
void matrix_print( Matrix *m, FILE *fp ) {

}

void matrix_clear( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			m->m[i][j] = 0.0;
}

void matrix_identity( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j )
				m->m[i][j] = 1.0;
 			else
				m->m[i][j] = 0.0;
		}
	}
}

double matrix_get( Matrix *m, int r, int c ) {
	return m->m[r][c];
}

void matrix_set( Matrix *m, int r, int c, double v ) {
	m->m[r][c] = v; 
}

void matrix_copy( Matrix *dest, Matrix *src ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			dest->m[i][j] = src->m[i][j];
}

// Not sure if this is correct 
void matrix_transpose( Matrix *m ) {
	Matrix b; // Temp matrix

	for ( int i = 0; i < 4; i++ )
        for ( int j = 0; j < 4; j++ ) 
            b.m[i][j] = m->m[j][i];

    for ( int i = 0; i < 4; i++ )
        for ( int j = 0; j < 4; j++ ) 
            m->m[i][j] = b.m[j][i];
}

void matrix_multiply( Matrix *left, Matrix *right, Matrix *m ) {
	for ( int i = 0; i < 4; i++) 
        for ( int j = 0; j < 4; j++ ) 
 	        m->m[i][j] = left->m[i][j] * right->m[i][j];
}

void matrix_xformPoint( Matrix *m, Point *p, Point *q ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			q->val[j] += m->m[i][j] * p->val[j]; 
}

void matrix_xformVector( Matrix *m, Vector *p, Vector *q ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			q->val[j] += m->m[i][j] * p->val[j]; 
}

void matrix_xformPolygon( Matrix *m, Polygon *p ) {
	for ( int k = 0; k < p->nVertex; k++ )
		for ( int i = 0; i < 4; i++ ) 
			for ( int j = 0; j < 4; j++ ) 
				p->vertex[k].val[j] += m->m[i][j] * p->vertex[k].val[j]; 
}

void matrix_xformPolyline( Matrix *m, Polyline *p ) {
	for ( int k = 0; k < p->numVertex; k++ )
		for ( int i = 0; i < 4; i++ ) 
			for ( int j = 0; j < 4; j++ ) 
				p->vertex[k].val[j] += m->m[i][j] * p->vertex[k].val[j]; 
}

void matrix_xformLine( Matrix *m, Line *line ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) {
			line->a.val[j] += m->m[i][j] * line->a.val[j]; 
			line->b.val[j] += m->m[i][j] * line->b.val[j]; 
		}
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
