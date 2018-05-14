#ifndef BEZIER_H

#define BEZIER_H

typedef struct {
	Point cpt[4]; 		// Control points
	double zbuff; 		
} BezierCurve;

typedef struct {
	Point cpt[16]; 		// Control points
	double zbuff; 		
} BezierSurface;

void bezierCurve_init( BezierCurve *b );
void bezierSurface_init( BezierSurface *b );
void bezierCurve_set( BezierCurve *b, Point *vlist );
void bezierSurface_set( BezierSurface *b, Point *vlist );
void bezierCurve_zBuffer( BezierCurve *b, double flag );
void bezierSurface_zBuffer( BezierSurface *b, double flag );
double ret_frac(double n1, double n2, float u);
void bezierCurve_draw( BezierCurve *b, Image *src, Color c );

#endif 