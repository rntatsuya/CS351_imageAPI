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
	ds->shade = ShadeFrame;
	
	printf("shade is %d\n", ds->shade);
	// printf("%d\n", ShadeFrame);
	
	return ds;
}

void drawstate_setColor( DrawState *s, Color c ) {
	s->color = c;
}

void drawstate_copy( DrawState *to, DrawState *from ) {
	to->color = from->color;
	to->shade = from->shade;
	
}
