#ifndef BEZIER_H

#define BEZIER_H

typedef struct {
	Point cpt[4]; 		// Control points
	int zbuff; 		
} BezierCurve;

typedef struct {
	Point cpt[16]; 		// Control points
	int zbuff; 		
} BezierSurface;

void bezierCurve_init( BezierCurve *b );
void bezierSurface_init( BezierSurface *b );
void bezierCurve_set( BezierCurve *b, Point *vlist );
void bezierSurface_set( BezierSurface *b, Point *vlist );
void bezierCurve_zBuffer( BezierCurve *b, int flag );
void bezierSurface_zBuffer( BezierSurface *b, int flag );
void bezierCurve_draw( BezierCurve *b, Image *src, Color c );

#endif BEZIER_H