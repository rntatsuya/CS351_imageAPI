#ifndef BEZIER_H

#define BEZIER_H

typedef struct {
	Point[4] cpt; 		// Control points
	int zbuff; 		
} BezierCurve;

typedef struct {
	Point[16] cpt; 		// Control points
	int zbuff; 		
} BezierSurface;

void bezierCurve_init( BezierCurve *b );
void bezierSurface_init( BezierSurface *b );
void bezierCurve_set( BezierCurve *b, Point *vlist );
void bezierSurface_set( BezierSurface *b, Point *vlist );
void bezierCurve_zBuffer( BezierCurve *p, int flag );
void bezierSurface_zBuffer( BezierCurve *p, int flag );
void bezierCurve_draw( BezierCurve *b, Image *src, Color c );

#endif BEZIER_H