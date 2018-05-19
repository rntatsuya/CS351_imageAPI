/**
 * Kimberly Required Image 2
 * Project 9
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

/*
  Adds to the module a unit cylinder, aligned along the Y-axis

  Takes in the number of subdivisions to use
 */
void cylinder( Module *mod, int sides );
void cylinder( Module *mod, int sides ) {
  Polygon p;
  Point xtop, xbot;
  double x1, x2, z1, z2;
  int i;

  polygon_init( &p );
  point_set3D( &xtop, 0, 1.0, 0.0 );
  point_set3D( &xbot, 0, 0.0, 0.0 );

  // make a fan for the top and bottom sides
  // and quadrilaterals for the sides
  for(i=0;i<sides;i++) {
    Point pt[4];
    Vector n[4];
    int j;

    x1 = cos( i * M_PI * 2.0 / sides );
    z1 = sin( i * M_PI * 2.0 / sides );
    x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
    z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

    point_copy( &pt[0], &xtop );
    point_set3D( &pt[1], x1, 1.0, z1 );
    point_set3D( &pt[2], x2, 1.0, z2 );

    polygon_set( &p, 3, pt );
    for(j=0;j<3;j++)
	    vector_set( &(n[j]), 0, 1, 0 );
    polygon_setNormals( &p, 3, n );
    module_polygon( mod, &p );

    point_copy( &pt[0], &xbot );
    point_set3D( &pt[1], x1, 0.0, z1 );
    point_set3D( &pt[2], x2, 0.0, z2 );

    polygon_set( &p, 3, pt );
    for(j=0;j<3;j++)
	    vector_set( &(n[j]), 0, -1, 0 );
    polygon_setNormals( &p, 3, n );
    module_polygon( mod, &p );

    point_set3D( &pt[0], x1, 0.0, z1 );
    point_set3D( &pt[1], x2, 0.0, z2 );
    point_set3D( &pt[2], x2, 1.0, z2 );
    point_set3D( &pt[3], x1, 1.0, z1 );

    vector_set( &n[0], x1, 0.0, z1 );
    vector_set( &n[1], x2, 0.0, z2 );
    vector_set( &n[2], x2, 0.0, z2 );
    vector_set( &n[3], x1, 0.0, z1 );
    
    polygon_set( &p, 4, pt );
    polygon_setNormals( &p, 4, n );
    module_polygon( mod, &p );
  }

  polygon_clear( &p );
}

// adds a cube centered on the origin of width 2x2x2 to the module
void cube( Module *mod );
void cube( Module *mod ) {
  Point pt[4];
  Polygon p;
  Vector n[4];
  int i;

  polygon_init( &p );
  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1, -1,  1 );
  point_set3D( &pt[2], -1,  1,  1 );
  point_set3D( &pt[3], -1,  1, -1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), -1, 0, 0 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

  point_set3D( &pt[0], 1, -1, -1 );
  point_set3D( &pt[1], 1, -1,  1 );
  point_set3D( &pt[2], 1,  1,  1 );
  point_set3D( &pt[3], 1,  1, -1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), 1, 0, 0 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1, -1,  1 );
  point_set3D( &pt[2],  1, -1,  1 );
  point_set3D( &pt[3],  1, -1, -1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), 0, -1, 0 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, 1, -1 );
  point_set3D( &pt[1], -1, 1,  1 );
  point_set3D( &pt[2],  1, 1,  1 );
  point_set3D( &pt[3],  1, 1, -1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), 0, 1, 0 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, -1 );
  point_set3D( &pt[1], -1,  1, -1 );
  point_set3D( &pt[2],  1,  1, -1 );
  point_set3D( &pt[3],  1, -1, -1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), 0, 0, -1 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

  point_set3D( &pt[0], -1, -1, 1 );
  point_set3D( &pt[1], -1,  1, 1 );
  point_set3D( &pt[2],  1,  1, 1 );
  point_set3D( &pt[3],  1, -1, 1 );
  polygon_set( &p, 4, pt );
  for(i=0;i<4;i++)
	  vector_set( &(n[i]), 0, 0, 1 );
  polygon_setNormals( &p, 4, n );
  module_polygon( mod, &p );

}

// makes 3 X-wing fighters in a loose formation
int main(int argc, char *argv[]) {

  Image *src;
  Module *cube;
  View3D view;
  Matrix vtm, gtm;
  DrawState *ds;
  Lighting *light;
  Color Red;
  Color Grey;
  Color Dark;
  Color Flame;
  Color Yellow;
	Color White;

	color_set(&White, 1.0, 1.0, 1.0 );
	color_set(&Flame, 1.0, 0.7, 0.2 );
	color_set(&Red, 1.0, 0.2, 0.1 );
	color_set(&Grey, 0.6, 0.65, 0.67 );
	color_set(&Dark, 0.2, 0.2, 0.2 );
	color_set(&Yellow, 1.0, 1.0, 0.0 );

	Color Blue;
	color_set(&Blue, 0.0, 0.0, 1.0 );

	Color SoftBlue;
	color_set(&SoftBlue, 0.1, 0.1, 0.7 );

	Color SoftRed;
	color_set(&SoftRed, 255/255.0, 153/255.0, 153/255.0 );

	Color Green;
	color_set(&Green, 0.0, 1.0, 0.0 );


  // set up the view
  point_set3D( &(view.vrp), 15, 30, 100 );
  vector_set( &(view.vpn), -20, -30, -100 );
  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 5.0;
  view.du = 1.6;
  view.dv = 0.9;
  view.f = 1;
  view.b = 200;
  view.screenx = 1280;
  view.screeny = 720;

  matrix_setView3D( &vtm, &view );
  matrix_identity( &gtm );

  cube = module_create();
  module_scale( cube, 5.0, 5.0, 5.0 );
  module_bodyColor( cube, &Flame );
  module_surfaceColor( cube, &Dark );
  module_cube( cube, 1 );

  // Pair 1
  module_identity(cube);
  module_bodyColor( cube, &Yellow );
  module_surfaceColor( cube, &Dark );
  module_translate( cube, 0, 2, 0 );
  cylinder( cube, 10 );

  module_identity(cube);
  module_bodyColor( cube, &Blue );
  module_surfaceColor( cube, &Dark );
  module_translate( cube, 0, -3, 0 );
  cylinder( cube, 10 );

  // Pair 2
  module_identity(cube);
  module_bodyColor( cube, &Green );
  module_surfaceColor( cube, &Dark );
  module_rotateZ( cube, 0, 1 );
  module_translate( cube, 3, 0, 0 );
  cylinder( cube, 10 );

  module_identity(cube);
  module_bodyColor( cube, &Blue );
  module_surfaceColor( cube, &Dark );
  module_rotateZ( cube, 0, 1 );
  module_translate( cube, -2, 0, 0 );
  cylinder( cube, 10 );

  // Pair 3
  module_identity(cube);
  module_bodyColor( cube, &Red );
  module_surfaceColor( cube, &Dark );
  module_rotateX( cube, 0, 1 );
  module_translate( cube, 0, 0, 2 );
  cylinder( cube, 10 );

  module_identity(cube);
  module_bodyColor( cube, &Red );
  module_surfaceColor( cube, &Dark );
  module_rotateX( cube, 0, 1 );
  module_translate( cube, 0, 0, -3 );
  cylinder( cube, 10 );

  // image
  src = image_create( view.screeny, view.screenx, 255 );
  ds = drawstate_create();
  point_copy(&(ds->viewer), &(view.vrp) );
  ds->shade = ShadeGouraud;

  light = lighting_create();
	// lighting_add(light, LightPoint, &White, NULL, &(view.vrp), 0.0, 0.0);
	lighting_add(light, LightPoint, &SoftRed, NULL, &(view.vrp), 0.0, 0.0);
	lighting_add(light, LightAmbient, &SoftBlue, NULL, &(view.vrp), 0.0, 0.0);

	// Create the animation by adjusting the GTM
	for(int frame=0;frame<30;frame++) {
		char buffer[256];
		printf("frame %d\n", frame);
		matrix_rotateY(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		matrix_rotateX(&gtm, cos(M_PI/30.0), sin(M_PI/30.0) );
		module_draw( cube, &vtm, &gtm, ds, light, src );

		sprintf(buffer, "p9-frame%03d.ppm", frame);
		image_write(src, buffer);
		image_reset(src);
	}


  module_delete( cube );

  image_free( src );

  return(0);
}