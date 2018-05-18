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
	
	Color c;
	color_set( &c, 1, 1, 1 );
	
	ds->color = c;
	ds->surfaceCoeff = 1.0;
	ds->shade = ShadeFrame;
	
	printf("shade is %d\n", ds->shade);
	// printf("%d\n", ShadeFrame);
	
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
