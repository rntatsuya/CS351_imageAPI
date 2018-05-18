/**
 * Kimberly and Tatsuya
 * drawstate.c
 */

#include "drawstate.h"

DrawState *drawstate_create( void ) {
	DrawState *ds = malloc(sizeof(DrawState));

	if (!ds) {
		printf("Ran out of memory while mallocing DrawState pointer in drawstate_create\n");
    	exit(-1);
	}
	
	Color c1,c2,c3;
	color_set( &c1, 1, 1, 1 );
	color_set( &c2, 1, 1, 1 );
	color_set( &c3, 1, 1, 1 );
	
	ds->color = c1;
	ds->body = c2;
	ds->surface = c3;
	ds->surfaceCoeff = 1.0;
	ds->shade = ShadeFrame;
	ds->zBufferFlag = 0;

	
	return ds;
}

void drawstate_setColor( DrawState *s, Color c ) {
	s->color = c;
}

void drawstate_setBody( DrawState *s, Color c ) {
	s->body = c;
}

void drawstate_setSurface( DrawState *s, Color c ) {
	s->surface = c;
}

void drawstate_setSurfaceCoeff( DrawState *s, float f ) {
	s->surfaceCoeff = f;
}


void drawstate_copy( DrawState *to, DrawState *from ) {
	to->color = from->color;
	to->body = from->body;
	to->surface = from->surface;
	to->surfaceCoeff = from->surfaceCoeff;
	to->shade = from->shade;
	
}
