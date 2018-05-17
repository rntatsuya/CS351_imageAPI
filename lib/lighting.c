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

	return l;
}

void lighting_init( Lighting *l ) {
	l->nLights = 0;
	int i;
	for (i=0; i<MAX_LIGHTS; i++)
		l->light[i] = (Light *)NULL;
}

void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness ) {

	if (l->nLights < MAX_LIGHTS) {
		Light *light = malloc(sizeof(Light));
		light->type = type;
		light->color = c;
		light->direction = dir;
		light->position = pos;
		light->cutoff = cutoff;
		light->sharpness = sharpness;
		l->light[l->nLights] = light;
		l->nLights++;
	}
	
}

void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, Color *Cb, Color *Cs, float s, int oneSided, Color *c ) {
	int i;

	// idk why bruce said to normalize an already normalized vector o_O
	vector_normalize(N);
	vector_normalize(V);

	// do some summation in a loop through each light in the lighting light array
	for (i=0; i<MAX_LIGHTS; i++) {
		if (!l->light[i])
			break;
		
		float r_sum = 0.0;
		float g_sum = 0.0;
		float b_sum = 0.0;
		
		switch (l->light[i]->type) {
			case LightNone : {
				
				break;
			}
			case LightAmbient : {
				if (r_sum < 1.0)
					r_sum += l->light[i]->color->c[0] * Cb->c[0];
				if (g_sum < 1.0)
					g_sum += l->light[i]->color->c[1] * Cb->c[1];
				if (b_sum < 1.0)
					b_sum += l->light[i]->color->c[2] * Cb->c[2];
				
				printf("ambient light %d: %.2f %.2f %.2f\n", i, r_sum, g_sum, b_sum);
				
				break;
			}
			case LightDirect : {
				
				break;
			}
			case LightPoint : {	
				// calculate light vector (vector from Point p to light source position)
				Vector L, H;
				vector_set( &L, 
						l->light[i]->position->val[0] - p->val[0], 
						l->light[i]->position->val[1] - p->val[1], 
						l->light[i]->position->val[2] - p->val[2] );
				vector_normalize(&L);

				float sharp = l->light[i]->sharpness;

				double LdotN = vector_dot( &L, N );
				if ((LdotN < 0) && (oneSided == 1))
					continue;

				double VdotN = vector_dot( V, N  );
				if ((LdotN<0 && VdotN>0) || (LdotN>0 && VdotN<0))
					continue;

				// calculate halfway vector H
				vector_add( &L, V, &H );
				vector_elementwise_div(&H, 2);
				double HdotN = vector_dot( &H, N  );
				if (LdotN < 0) {
					LdotN *= (-1.0);
					HdotN *= (-1.0);
				}

				// what value should we use for the smoothness coefficient?? => Use s in param or sharpness property of light struct?
				if (r_sum < 1.0)
					r_sum += (Cb->c[0])*(l->light[i]->color->c[0])*LdotN 
						+ (l->light[i]->color->c[0])*(Cs->c[0])*pow(HdotN,s);

				if (g_sum < 1.0)
					g_sum += (Cb->c[1])*(l->light[i]->color->c[1])*LdotN 
						+ (l->light[i]->color->c[1])*(Cs->c[1])*pow(HdotN,s);

				if (b_sum < 1.0)			
					b_sum += (Cb->c[2])*(l->light[i]->color->c[2])*LdotN
						+ (l->light[i]->color->c[2])*(Cs->c[2])*pow(HdotN,s);
				
				printf("point light %d: %.2f %.2f %.2f\n", i, r_sum, g_sum, b_sum);
				
				break;
			}
			case LightSpot : {
				
				break;
			}

		}
		
		if (r_sum > 1.0)
			r_sum = 1.0;
		if (g_sum > 1.0)
			g_sum = 1.0;
		if (b_sum > 1.0)
			b_sum = 1.0;
		
		c->c[0] = r_sum;
		c->c[1] = g_sum;
		c->c[2] = b_sum;		
	}

}

