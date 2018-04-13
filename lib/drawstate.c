/**
 * Kimberly and Tatsuya
 * drawstate.c
 */

#include "graphics.h"

DrawState *drawstate_create( void ) {
	DrawState *ds = malloc(sizeof(DrawState));

	if (!ds) {
		printf("Ran out of memory while mallocing DrawState pointer in drawstate_create\n");
    	exit(-1);
	}

	return ds;
}

void drawstate_setColor( DrawState *s, Color c ) {
	s->color = c;
}

void drawstate_copy( DrawState *to, DrawState *from ) {
	to->color = from->color;
}
