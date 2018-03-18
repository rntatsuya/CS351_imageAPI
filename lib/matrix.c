/**
 * Kimberly and Tatsuya
 * matrix.c
 */

//////////////////////////////
// Generic Matrix Functions //
//////////////////////////////
 
void matrix_print( Matrix *m, FILE *fp ) {

}

void matrix_clear( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			m[i * 4 + j] = 0.0;
}

void matrix_identity( Matrix *m ) {
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j )
				m[i * 4 + j] = 1.0;
 			else
				m[i * 4 + j] = 0.0;
		}
	}
}

double matrix_get( Matrix *m, int r, int c ) {
	return m[r * 4 + c];
}

void matrix_set( Matrix *m, int r, int c, double v ) {
	m[r * 4 + c] = v; 
}

void matrix_copy( Matrix *dest, Matrix *src ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			dest[i * 4 + j] = src[i * 4 + j];
}

void matrix_transpose( Matrix *m ) {
}

void matrix_multiply( Matrix *left, Matrix *right, Matrix *m ) {
	for (j = 0; j < 4; ++j) {
        for (i = 0; i < 4; ++i) {
        	int d = i * 4 + j;
 	        m[d] = left[d] * right[d];
 	    }
 	}
}

void matrix_xformPoint( Matrix *m, Point *p, Point *q ) {
	for ( int i = 0; i < 4; i+=4 ) 
		q->val[i] = m[i]*p[0] + m[i+1]*p[1] + m[i+2]*p[2] + m[i+3]*p[3];
}

void matrix_xformVector( Matrix *m, Vector *p, Vector *q ) {
	for ( int i = 0; i < 4; i+=4 ) 
		q->val[i] = m[i]*p[0] + m[i+1]*p[1] + m[i+2]*p[2] + m[i+3]*p[3];
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

void matrix_rotateY( Matrix *m, double cth, double st h {

}

void matrix_rotateXYZ( Matrix *m, Vector *u, Vector *v, Vector  * {

}

void matrix_shearZ( Matrix *m, double shx, double shy ) {

}

void matrix_perspective( Matrix *m, double d ) {

}
