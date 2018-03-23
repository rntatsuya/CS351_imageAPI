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

	if (fp == NULL) {
		fprintf(stderr, "Can't open output file!\n");
		exit(1);
	}
	
	int i,j;
	
	fprintf(fp, "[ [");
    for (i=0;i<4;i++) {
		if (i != 0)
			fprintf(fp, "  [");
		for (j=0;j<4;j++) {
			fprintf(fp, "%.2f ", m->m[i][j]);
		}
		fprintf(fp, "]");
		if (i==3)
			fprintf(fp, " ]");
		fprintf(fp, "\n");
    }

// 	for ( int i = 0 ; i < 4; i++ ) {
// 		fprintf(fp, "%.2f, %.2f, %.2f, %.2f \n", 
// 			m->m[i][0], m->m[i][1], m->m[i][2], m->m[i][3]);
// 	}
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
 	int i,j,k;
 	Matrix out;
 	// make output matrix in case input and output matrix have the same address
 	matrix_clear(&out);
 	
 	for (k=0;k<4;k++) {
    	for (i=0;i<4;i++) {
	    	for (j=0;j<4;j++) {
			out.m[i][k] += left->m[i][j] * right->m[j][k];
			}
    	}
  	}
  
	matrix_copy( m, &out );
}

void matrix_xformPoint( Matrix *m, Point *p, Point *q ) {
	for ( int i = 0; i < 4; i++ ) {
		q->val[i] = 0;
		for ( int j = 0; j < 4; j++ ) {
			q->val[i] += m->m[i][j] * p->val[j]; 
// 			printf("[%d](%.2f) += [%d][%d](%.2f) * [%d](%.2f)\n", i, q->val[i], j,i, m->m[j][i], j, p->val[j]);
		}
	}
}

void matrix_xformVector( Matrix *m, Vector *p, Vector *q ) {
	for ( int i = 0; i < 4; i++ ) {
		q->val[i] = 0;
		for ( int j = 0; j < 4; j++ ) 
			q->val[i] += m->m[i][j] * p->val[j]; 
	}
}

void matrix_xformPolygon( Matrix *m, Polygon *p ) {
	Point temp;
	
	for ( int k = 0; k < p->nVertex; k++ ) {
		// copy point to separate left and right hand side of equation below
// 		point_copy(&temp, &p->vertex[k]);
// 		for ( int i = 0; i < 4; i++ ) {
// 			for ( int j = 0; j < 4; j++ ) 
				matrix_xformPoint( m, &p->vertex[k], &temp );
				point_copy(&p->vertex[k], &temp);
// 				p->vertex[k].val[i] += m->m[i][j] * temp.val[j]; 
// 		}
	}
}

void matrix_xformPolyline( Matrix *m, Polyline *p ) {
	for ( int k = 0; k < p->numVertex; k++ )
		for ( int i = 0; i < 4; i++ ) 
			for ( int j = 0; j < 4; j++ ) 
				p->vertex[k].val[i] += m->m[i][j] * p->vertex[k].val[j]; 
}

void matrix_xformLine( Matrix *m, Line *line ) {
	for ( int i = 0; i < 4; i++ ) 
		for ( int j = 0; j < 4; j++ ) {
			line->a.val[i] += m->m[i][j] * line->a.val[j]; 
			line->b.val[i] += m->m[i][j] * line->b.val[j]; 
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

	t.m[0][0] = cth;
	t.m[1][1] = cth;

	t.m[0][1] = -sth;
	t.m[1][0] = sth;

	t.m[2][2] = 1;
	t.m[3][3] = 1;
	
	printf("Before rotate\n");
	matrix_print(m, stdout);
	matrix_print(&t, stdout);
	matrix_multiply( &t, m, m );
// 	printf("After rotate\n");
// 	matrix_print(m, stdout);
}

void matrix_translate2D( Matrix *m, double tx, double ty ) {
	Matrix t; // Temp
	// for ( int i = 0; i < 4; i++ ) {
// 		for ( int j = 0; j < 4; j++ ) {
// 			if ( i == j ) 
// 				t.m[i][j] = 1;
// 			else 
// 				t.m[i][j] = 0;
// 		}
// 	}
	matrix_clear(&t);
	
	t.m[0][0] = 1;
	t.m[1][1] = 1;
	t.m[2][2] = 1;
	t.m[3][3] = 1;

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
	
	t.m[1][1] = cth;
	t.m[2][2] = cth;

	t.m[1][2] = -sth;
	t.m[2][1] = sth;

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

	t.m[0][0] = cth;
	t.m[2][2] = cth;

	t.m[0][2] = sth;
	t.m[2][0] = -sth;	

	matrix_multiply( &t, m, m );
}


void matrix_rotateXYZ( Matrix *m, Vector *u, Vector *v, Vector *w ) {

	m->m[0][0] = u->val[0];
	m->m[0][1] = u->val[1];
	m->m[0][2] = u->val[2];
	m->m[0][3] = 0;

	m->m[1][0] = v->val[0];
	m->m[1][1] = v->val[1];
	m->m[1][2] = v->val[2];
	m->m[1][3] = 0;

	m->m[2][0] = w->val[0];
	m->m[2][1] = w->val[1];
	m->m[2][2] = w->val[2];
	m->m[2][3] = 0;
	
	m->m[3][0] = 0;
	m->m[3][1] = 0;
	m->m[3][2] = 0;
	m->m[3][3] = 1;
	
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
