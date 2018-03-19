/**
 * Kimberly and Tatsuya
 * matrix.c
 */

#include "matrix.h"
#include "stdlib.h"

//////////////////////////////
// Generic Matrix Functions //
//////////////////////////////
 
void matrix_print( Matrix *m, FILE *fp ) {
	char *filename = "matrix_content.txt";

	fp = fopen(filename, "w");

	if (fp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", filename);
		exit(1);
	}

	for ( int i = 0 ; i < 4; i++ ) {
		fprintf(fp, "%.2f, %.2f, %.2f, %.2f \n", 
			m->m[i][0], m->m[i][1], m->m[i][2], m->m[i][3]);
	}
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

void matrix_transpose( Matrix *m ) {
	Matrix b; // Temp matrix
	for ( int i = 0; i < 4; i++ )
        for ( int j = 0; j < 4; j++ ) 
            b.m[i][j] = m->m[j][i];

    matrix_copy( m, &b );
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
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if (( i == 2 && j == 2 ) || ( i == 3 && j == 3 ))
				t.m[i][j] = 1; 
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][0] = sx; 
	t.m[1][1] = sy; 

	matrix_multiply( &t, m, m );
}

void matrix_rotateZ( Matrix *m, double cth, double sth ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) 
			t.m[i][j] = 0;

	t.m[0][0] = cos(cth);
	t.m[1][1] = cos(cth);

	t.m[0][1] = -sin(sth);
	t.m[1][0] = sin(sth);

	t.m[2][2] = 1;
	t.m[3][3] = 1;

	matrix_multiply( &t, m, m );
}

void matrix_translate2D( Matrix *m, double tx, double ty ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j ) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][3] = tx;
	t.m[1][3] = ty;

	matrix_multiply( &t, m, m );
}

void matrix_shear2D( Matrix *m, double shx, double shy ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j ) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][1] = shx;
	t.m[1][0] = shy;

	matrix_multiply( &t, m, m );
}


/////////////////////////
// 3D Matrix functions //
/////////////////////////

void matrix_translate( Matrix *m, double tx, double ty, double tz ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( i == j ) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][3] = tx;
	t.m[1][3] = ty;
	t.m[2][3] = tz;

	matrix_multiply( &t, m, m );
}

void matrix_scale( Matrix *m, double sx, double sy, double sz ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ )
			t.m[i][j] = 0;

	t.m[0][0] = sx;
	t.m[1][1] = sy;
	t.m[2][2] = sz;
	t.m[3][3] = 1;

	matrix_multiply( &t, m, m );
}

void matrix_rotateX( Matrix *m, double cth, double sth ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( (i == 0 && j == 0) || (i == 3 && j == 3) ) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}
	
	t.m[1][1] = cos(cth);
	t.m[1][1] = cos(cth);

	t.m[1][2] = -sin(sth);
	t.m[2][1] = sin(sth);

	matrix_multiply( &t, m, m );
}

void matrix_rotateY( Matrix *m, double cth, double sth ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( (i == 1 && j == 1) || (i == 3 && j == 3) ) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][0] = cos(cth);
	t.m[2][2] = cos(cth);

	t.m[0][2] = sin(sth);
	t.m[2][0] = -sin(sth);	

	matrix_multiply( &t, m, m );
}


void matrix_rotateXYZ( Matrix *m, Vector *u, Vector *v, Vector *w ) {
	Matrix t; // Temp

	matrix_identity(m);
	t.m[0][0] = u->val[0];
	t.m[0][1] = u->val[1];
	t.m[0][2] = u->val[2];

	t.m[1][0] = v->val[0];
	t.m[1][1] = v->val[1];
	t.m[1][2] = v->val[2];

	t.m[2][0] = w->val[0];
	t.m[2][1] = w->val[1];
	t.m[2][2] = w->val[2];

	matrix_multiply( &t, m, m );
}

void matrix_shearZ( Matrix *m, double shx, double shy ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if (i == j) 
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[0][2] = shx;
	t.m[1][2] = shy;

	matrix_multiply( &t, m, m );
}

void matrix_perspective( Matrix *m, double d ) {
	Matrix t; // Temp
	for ( int i = 0; i < 4; i++ ) {
		for ( int j = 0; j < 4; j++ ) {
			if ( (i != 4) && (i == j) )
				t.m[i][j] = 1;
			else 
				t.m[i][j] = 0;
		}
	}

	t.m[3][2] = 1 / d;

	matrix_multiply( &t, m, m );
}
