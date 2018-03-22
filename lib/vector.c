/**
 * Kimberly and Tatsuya
 * vector.c
 */

#include "vector.h"
#include <stdlib.h>
// #include <math.h>

void vector_set( Vector *v, double x, double y, double z ) {
	v->val[0] = x;
	v->val[1] = y;
	v->val[2] = z;
}

void vector_print( Vector *v, FILE *fp ) {
// 	char *filename = "vector_content.txt";
// 
// 	fp = fopen(filename, "w");

	if (fp == NULL) {
		fprintf(stderr, "Can't open output file!\n");
		exit(1);
	}

	fprintf(fp, "(x, y, z, h): (%lf, %lf, %lf, %lf)\n", 
		v->val[0],
		v->val[1],
		v->val[2],
		v->val[3]
	);
}

void vector_copy( Vector *dest, Vector *src ) {
	dest->val[0] = src->val[0];
	dest->val[1] = src->val[1];
	dest->val[2] = src->val[2];
	dest->val[3] = src->val[3];
}

double vector_length( Vector *v ) {
	return ( sqrt( v->val[0]*v->val[0] 
		+ v->val[1]*v->val[1] 
		+ v->val[2]*v->val[2] ) );
}

void vector_normalize( Vector *v ) {
	double l = vector_length(v);
	v->val[0] /= l; 
	v->val[1] /= l; 
	v->val[2] /= l; 
}

double vector_dot( Vector *a, Vector *b ) {
	return ( a->val[0]*b->val[0] 
		+ a->val[1]*b->val[1] 
		+ a->val[2]*b->val[2] );
}

void vector_cross( Vector *a, Vector *b, Vector *c ) {
	c->val[0] = a->val[1]*b->val[2] - a->val[2]*b->val[1];
	c->val[1] = a->val[2]*b->val[0] - a->val[0]*b->val[2];
	c->val[2] = a->val[0]*b->val[1] - a->val[1]*b->val[0];
}