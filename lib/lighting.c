/**
 * Kimberly and Tatsuya
 * lighting.c
 */

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

void light_init( Light *light ) {
	light->type = LightNone;
	light->color = (Color *)NULL;
	light->direction = (Vector *)NULL;
	light->position = (Point *)NULL;
	light->cutoff = 0.0;
	light->sharpness = 0.0;
}

void light_copy( Light *to, Light *from ) {
	to->type = from->type;
	to->color = from->color;
	to->direction = from->direction;
	to->position = from->position;
	to->cutoff = from->cutoff;
	to->sharpness = from->sharpness;
}

Lighting *lighting_create( void ) {
	Lighting *l = malloc(sizeof(Lighting));
	l->nLights = 0;
	
	int i;
	for (i=0; i<MAX_LIGHTS; i++) {
		l->light[i] = (Light *)NULL;
	}
// 	l->light 
}
void lighting_init( Lighting *l ) {
	l->nLights = 0;
	int i;
	for (i=0; i<MAX_LIGHTS; i++) {
		l->light[i] = (Light *)NULL;
	}
}

void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness ) {
	
	int i;
	for (i=0; i<MAX_LIGHTS; i++) {
		if (l->light[i]) 
			continue;
		else {
			Light *light = malloc(sizeof(Light));
	
			light->type = type;
			light->color = *c;
			light->direction = *dir;
			light->position = *pos;
			light->cutoff = cutoff;
			light->sharpness = sharpness;
			l->light[i] = &light;
			break;
		}
	}
}

void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, Color *Cb, Color *Cs, float s, int oneSided, Color *c ) {
	int i;
	
	// do some summation in a loop through each light in the lighting light array
	for (i=0; i<MAX_LIGHTS; i++) {
		if (!l->light[i])
			break;
		
		float r_sum = 0.0;
		float g_sum = 0.0;
		float b_sum = 0.0;
		
		switch (l->light[i].type) {
			case LightNone : {
				
				break;
			}
			case LightAmbient : {
				if (r_sum < 1.0)
					r_sum += l->light[i].color.c[0] * Cb->c[0];
				if (g_sum < 1.0)
					g_sum += l->light[i].color.c[1] * Cb->c[1];
				if (b_sum < 1.0)
					b_sum += l->light[i].color.c[2] * Cb->c[2];
				break;
			}
			case LightDirect : {
				
				break;
			}
			case LightPoint : {
				// calculate halfway vector H
				Vector *H = malloc(sizeof(Vector));
				vector_add( &l->light[i].direction, V, H );
				vector_elementwise_div(H, 2);
				
				// what value should we use for the smoothness coefficient??
				if (r_sum < 1.0)
					r_sum += Cb->c[0]*l->light[i].color.c[0]*vector_dot( &(l->light[i].direction), N ) 
						+ l->light[i].color.c[0]*Cs->c[0]*vector_dot( H, N );
				if (g_sum < 1.0)
					g_sum += Cb->c[1]*l->light[i].color.c[1]*vector_dot( &(l->light[i].direction), N ) 
						+ l->light[i].color.c[1]*Cs->c[1]*vector_dot( H, N );
				if (b_sum < 1.0)			
					b_sum += Cb->c[2]*l->light[i].color.c[2]*vector_dot( &(l->light[i].direction), N ) 
						+ l->light[i].color.c[2]*Cs->c[2]*vector_dot( H, N );
				break;
			}
			case LightSpot : {
// 				if ( < ) 
				
				
				break;
			}

		}
		
		if (r_sum > 1.0)
			r_sum = 1.0;
		if (g_sum > 1.0)
			g_sum = 1.0;
		if (b_sum > 1.0)
			b_sum = 1.0;
	}

}

