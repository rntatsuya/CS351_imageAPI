/**
 * Kimberly and Tatsuya
 * bezier.c
 */

#include "graphics.h"


void bezierCurve_init( BezierCurve *b ) {
	b->zbuff = 1;
	Point[4] cpt; 		// Control points
	
	int i;
	for (i=0; i<4; i++)
		point_set3D(cpt[0], 0.25 * i, 0, 0);
	
	bezierCurve_set(b, cpt);
} 

void bezierSurface_init( BezierSurface *b ) {
	b->zbuff = 1;
	Point[4] cpt; 		// Control points
	
	int i,j;
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) 
			point_set3D(cpt[0], 0.25*i, 0.25*j, 0);
	}
} 

void bezierCurve_set( BezierCurve *b, Point *vlist ) {
	int i;
	for (i=0; i<4; i++)
		b->cpt[i] = vlist[i];
} 

void bezierSurface_set( BezierSurface *b, Point *vlist ) {
	int i;
	for (i=0; i<16; i++)
		b->cpt[i] = vlist[i];
} 

void bezierCurve_zBuffer( BezierCurve *b, int flag ) {
	b->zbuff = flag;
} 

void bezierSurface_zBuffer( BezierSurface *b, int flag ) {
	b->zbuff = flag;
} 

void bezierCurve_draw( BezierCurve *b, Image *src, Color c ) {
	
} 

 