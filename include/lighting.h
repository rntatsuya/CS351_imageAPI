#ifndef LIGHTING_H

#define LIGHTING_H

#define MAX_LIGHTS 64

typedef enum {
	LightNone,
	LightAmbient,
	LightDirect,
	LightPoint,
	LightSpot,
} LightType;

typedef struct {
	LightType type;
	Color *color;
	Vector *direction;
	Point *position;
	float cutoff; // stores the cosine of the cutoff angle of a spotlight
	float sharpness; // coefficient of the falloff function (power for cosine)
} Light;

typedef struct {
	int nLights;
	Light *light[MAX_LIGHTS];
} Lighting;

void light_init( Light *light );
void light_copy( Light *to, Light *from );
Lighting *lighting_create( void );
void lighting_init( Lighting *l );
void lighting_add( Lighting *l, LightType type, Color *c, Vector *dir, Point *pos, float cutoff, float sharpness );
void lighting_shading( Lighting *l, Vector *N, Vector *V, Point *p, Color *Cb, Color *Cs, float s, int oneSided, Color *c );

#endif