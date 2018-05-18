#ifndef DRAWSTATE_H

#define DRAWSTATE_H

#include "color.h"
#include "line.h"

typedef enum {			// Determines how an object is drawn into the image
	ShadeFrame,			// Draw only borders of objects (polygons included) 
	ShadeConstant, 		// Draw object using current fg color, fill polygons
	ShadeDepth,
	ShadeFlat,
	ShadeGouraud,
	ShadePhong
} ShadeMethod;

typedef struct {		// Specifies how object is drawn into the image
	Color color;		// Foreground color, used in the default drawing mode
	Color flatColor;
	Color body;
	Color surface; 
	float surfaceCoeff;
	ShadeMethod shade;
	int zBufferFlag;	
	Point viewer;		// Point representing the view location in 3D (Like VRP in 3D)
} DrawState;			

DrawState *drawstate_create( void );
void drawstate_setColor( DrawState *s, Color c );
void drawstate_setBody( DrawState *s, Color c );
void drawstate_setSurface( DrawState *s, Color c );
void drawstate_setSurfaceCoeff( DrawState *s, float f );
void drawstate_copy( DrawState *to, DrawState *from );


#endif