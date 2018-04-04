/**
 * Kimberly  
 * Project 5
 * Required 3D Scene
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main( int argc, char *argv[] ) {
	printf("Creating icosphere...\n");
  
  const int rows = 600;
  const int cols = 800;
  const int numFace = 20;
  View3D view;
  Matrix vtm;
  Polygon side[numFace];
  Polygon tpoly;
  Point  tv[3];
  Point  v[12];
  Color Red;
  Color Green;
  Image *src;
  int i;

  // set some colors
  color_set( &Red, 1, 0, 0 );
  color_set( &Green, 0, 1, 0 );

  // initialize polygons
  for(i=0;i<numFace;i++) 
    polygon_init( &side[i] );

  // corners of a cube, centered at (0, 0, 0)

  point_set3D( &v[0], 0, 0, 1 );
  point_set3D( &v[1], -0.72, -0.52, 0.44 );
  point_set3D( &v[2], 0.27, -0.85, 0.44 );
  point_set3D( &v[3], 0.89, 0.00, 0.44 );
  point_set3D( &v[4], 0.27, 0.85, 0.44 );
  point_set3D( &v[5], -0.72, 0.52, 0.44 );

  point_set3D( &v[6], 0.72, 0.52, -0.44 );
  point_set3D( &v[7], -0.27, 0.85, -0.44 );
  point_set3D( &v[8], -0.89, 0.00, -0.44 );
  point_set3D( &v[9], -0.27, -0.85, -0.44 );
  point_set3D( &v[10], 0.72, -0.52, -0.44 );
  point_set3D( &v[11], 0, 0, -1 );

  // Top 
  point_copy( &tv[0], &v[0] );
  point_copy( &tv[1], &v[1] );
  point_copy( &tv[2], &v[2] );
  polygon_set( &side[0], 3, tv );

  point_copy( &tv[1], &v[2] );
  point_copy( &tv[2], &v[3] );
  polygon_set( &side[1], 3, tv );

  point_copy( &tv[1], &v[3] );
  point_copy( &tv[2], &v[4] );
  polygon_set( &side[2], 3, tv );

  point_copy( &tv[1], &v[4] );
  point_copy( &tv[2], &v[5] );
  polygon_set( &side[3], 3, tv );

  point_copy( &tv[1], &v[5] );
  point_copy( &tv[2], &v[1] );
  polygon_set( &side[4], 3, tv );

  // Bottom
  point_copy( &tv[0], &v[11] );
  point_copy( &tv[1], &v[6] );
  point_copy( &tv[2], &v[7] );
  polygon_set( &side[5], 3, tv );

  point_copy( &tv[1], &v[7] );
  point_copy( &tv[2], &v[8] );
  polygon_set( &side[6], 3, tv );

  point_copy( &tv[1], &v[8] );
  point_copy( &tv[2], &v[9] );
  polygon_set( &side[7], 3, tv );

  point_copy( &tv[1], &v[9] );
  point_copy( &tv[2], &v[10] );
  polygon_set( &side[8], 3, tv );

  point_copy( &tv[1], &v[10] );
  point_copy( &tv[2], &v[6] );
  polygon_set( &side[9], 3, tv );

  // First half of middle
  point_copy( &tv[0], &v[1] );
  point_copy( &tv[1], &v[2] );
  point_copy( &tv[2], &v[9] );
  polygon_set( &side[10], 3, tv );

  point_copy( &tv[0], &v[2] );
  point_copy( &tv[1], &v[3] );
  point_copy( &tv[2], &v[10] );
  polygon_set( &side[11], 3, tv );

  point_copy( &tv[0], &v[3] );
  point_copy( &tv[1], &v[4] );
  point_copy( &tv[2], &v[6] );
  polygon_set( &side[12], 3, tv );

  point_copy( &tv[0], &v[4] );
  point_copy( &tv[1], &v[5] );
  point_copy( &tv[2], &v[7] );
  polygon_set( &side[13], 3, tv );

  point_copy( &tv[0], &v[5] );
  point_copy( &tv[1], &v[1] );
  point_copy( &tv[2], &v[8] );
  polygon_set( &side[14], 3, tv );

  // Second half of middle
  point_copy( &tv[0], &v[6] );
  point_copy( &tv[1], &v[7] );
  point_copy( &tv[2], &v[4] );
  polygon_set( &side[15], 3, tv );

  point_copy( &tv[0], &v[7] );
  point_copy( &tv[1], &v[8] );
  point_copy( &tv[2], &v[5] );
  polygon_set( &side[16], 3, tv );

  point_copy( &tv[0], &v[8] );
  point_copy( &tv[1], &v[9] );
  point_copy( &tv[2], &v[1] );
  polygon_set( &side[17], 3, tv );

  point_copy( &tv[0], &v[9] );
  point_copy( &tv[1], &v[10] );
  point_copy( &tv[2], &v[2] );
  polygon_set( &side[18], 3, tv );

  point_copy( &tv[0], &v[10] );
  point_copy( &tv[1], &v[6] );
  point_copy( &tv[2], &v[3] );
  polygon_set( &side[19], 3, tv );

  // grab command line argument to determine viewpoint
  // and set up the view structure
  if( argc > 1 ) {
    float alpha = atof( argv[1] );
    if( alpha < 0.0 || alpha > 1.0 )
      alpha = 0.0;

    point_set3D( &(view.vrp), 3*alpha, 2*alpha, -2*alpha - (1.0-alpha)*3 );
  }
  else {
    point_set3D( &(view.vrp), 3, 2, -2 );
  }
  vector_set( &(view.vpn), -view.vrp.val[0], -view.vrp.val[1], -view.vrp.val[2] );

  vector_set( &(view.vup), 0, 1, 0 );
  view.d = 1;  // focal length
  view.du = 2;
  view.dv = view.du * (float)rows / cols;
  view.f = 0; // front clip plane
  view.b = 4; // back clip plane
  view.screenx = cols;
  view.screeny = rows;

  matrix_setView3D( &vtm, &view );

  // create image
  src = image_create( rows, cols, 255 );

  // use a temprary polygon to transform stuff
  polygon_init( &tpoly );

  printf("Drawing Polygons\n");
  for(i=0;i<numFace;i++) {
    polygon_copy( &tpoly, &side[i] );
    matrix_xformPolygon( &vtm, &tpoly );

    // normalize by homogeneous coordinate before drawing
    polygon_normalize( &tpoly );

    polygon_drawFrame( &tpoly, src, Green );
    polygon_print( &tpoly, stdout );
  }

  printf("Writing image\n");
  image_write( src, "icosphere.ppm" );

	return(0); 
}