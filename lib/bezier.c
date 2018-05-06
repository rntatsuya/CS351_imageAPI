/**
 * Kimberly and Tatsuya
 * bezier.c
 */

#include "graphics.h"


void bezierCurve_init( BezierCurve *b ) {
	b->zbuff = 1;
	Point cpt[4]; 		// Control points
	
	int i;
	for (i=0; i<4; i++)
		point_set3D(&cpt[0], 0.25 * i, 0, 0);
	
	bezierCurve_set(b, cpt);
} 

void bezierSurface_init( BezierSurface *b ) {
	b->zbuff = 1;
	Point cpt[4]; 		// Control points
	
	int i,j;
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) 
			point_set3D(&cpt[0], 0.25*i, 0.25*j, 0);
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

double ret_frac(double n1, double n2, float u) {
// 	printf("(%.2f + %.2f) * %.2f = %.2f\n", n1, n2, u, (n1 + n2) * u);
	return (n1 + n2) * u;
}

void bezierCurve_draw( BezierCurve *b, Image *src, Color c ) {
	// check if bounding box of control points is less than 10
	// draw if so
	printf("hey\n");
	int i;
	float min_x = b->cpt[0].val[0];
	float max_x = b->cpt[0].val[0];
	float min_y = b->cpt[0].val[1];
	float max_y = b->cpt[0].val[1];
	for (i=1; i<4; i++) {
		if ( b->cpt[i].val[0] < min_x)
			min_x = b->cpt[i].val[0];
		else if ( b->cpt[i].val[0] > max_x)
			max_x = b->cpt[i].val[0];
		if ( b->cpt[i].val[1] < min_y)
			min_y = b->cpt[i].val[1];
		else if ( b->cpt[i].val[1] > max_y)
			max_y = b->cpt[i].val[1];
	}
	float max_side_length = max_x - min_x > max_y - min_y ? max_x - min_x : max_y - min_y;
	if (max_side_length < 10) {
		Line l;
		line_set2D(&l, b->cpt[0].val[0], b->cpt[0].val[1], b->cpt[1].val[0], b->cpt[1].val[1]);
		line_draw(&l, src, c);
		line_set2D(&l, b->cpt[1].val[0], b->cpt[1].val[1], b->cpt[2].val[0], b->cpt[2].val[1]);
		line_draw(&l, src, c);
		line_set2D(&l, b->cpt[2].val[0], b->cpt[2].val[1], b->cpt[3].val[0], b->cpt[3].val[1]);
		line_draw(&l, src, c);
		return;
	}
	
	// if not, subdivide the control points in the middle between each, and recursively 
	// call this func. for the two set of 4 control points
	BezierCurve b1;
	BezierCurve b2;
	Point p[7];
	Point p_n[7];
	float u = 0.5;
	
	// P0 
	point_set2D(&p[0], b->cpt[0].val[0], b->cpt[0].val[1]); 
	// P1
	point_set2D(&p[2], b->cpt[1].val[0], b->cpt[1].val[1]);
	// P2
	point_set2D(&p[4], b->cpt[2].val[0], b->cpt[2].val[1]);
	// P3
	point_set2D(&p[6], b->cpt[3].val[0], b->cpt[3].val[1]);
	// point between P0 and P1 => F0
	point_set2D(&p[1], ret_frac(p[0].val[0], p[2].val[0], u), ret_frac(p[0].val[1], p[2].val[1], u));
	// point between P1 and P2 => F1
	point_set2D(&p[3], ret_frac(p[2].val[0], p[4].val[0], u), ret_frac(p[2].val[1], p[4].val[1], u));
	// point between P2 and P3 => F2
	point_set2D(&p[5], ret_frac(p[4].val[0], p[6].val[0], u), ret_frac(p[4].val[1], p[6].val[1], u));


	// P0 => A0
	point_copy(&p_n[0], &p[0]);
	// F1 => A1
	point_copy(&p_n[1], &p[1]);
	// between A1 and F1 => A2
	point_set2D(&p_n[2], ret_frac(p_n[1].val[0], p[3].val[0], u),  ret_frac(p_n[1].val[1], p[3].val[1], u));
	// start making points from other side 
	// P3 => B3
	point_copy(&p_n[6], &p[6]);
	// F2 => B2
	point_copy(&p_n[5], &p[5]);
	// between B2 and F1 => B1
	point_set2D(&p_n[4], ret_frac(p_n[5].val[0], p[3].val[0], u),  ret_frac(p_n[5].val[1], p[3].val[1], u));
	// between A2 and B1 => A3 & B0
	point_set2D(&p_n[3], ret_frac(p_n[4].val[0], p_n[2].val[0], u),  ret_frac(p_n[4].val[1], p_n[2].val[1], u));
	

	printf("Original Points\n");
	for (i=0; i<4; i++) {
		point_print(&b->cpt[i], stdout);
	}
	printf("Original + Half Points\n");
	for (i=0; i<7; i++) {
		point_print(&p[i], stdout);
	}
	printf("Subdivided Points\n");
	for (i=0; i<7; i++) {
		point_print(&p_n[i], stdout);
	}

	bezierCurve_set( &b1, &p_n[0] );
	bezierCurve_set( &b2, &p_n[3] );
	bezierCurve_draw( &b1, src, c);
	bezierCurve_draw( &b2, src, c);	
	

} 

 