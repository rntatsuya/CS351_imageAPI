/**
 * Kimberly  
 * Project 5
 * Required 2D Scene
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main( int argc, char *argv[] ) {
	printf("Creating 2D Scene...\n");
	Image *src;
  const int rows = 600;
  const int cols = 800;
  const int Resolution = 50;
  
  Color Yellow;
  Color Yellow2;
  Color Yellow_White;
  
  Point unitCircle[Resolution];
  Point unitTriangle[3];
  
  Point pt[Resolution];
  Point ptt[Resolution];
  int i, index = 0;
  
  Matrix VTM, GTM, LTM;
  Polygon *sun[50];
  Color color[50];
  
  double theta = 0.0;

  color_set(&Yellow, 245/255.0, 255/255.0, 85/255.0);
  color_set(&Yellow2, 255/255.0, 252/255.0, 117/255.0);
  color_set(&Yellow_White, 255/255.0, 253/255.0, 209/255.0);

  if(argc > 1) {
    theta = atoi(argv[1]);
  }
  printf("Drawing sun with orientation %.2f degrees\n", theta);

  srand(42);

  src = image_create(rows, cols, 255);

  // initialize the three matrices
  matrix_identity(&VTM);
  matrix_identity(&GTM);
  matrix_identity(&LTM);

  // Fix world coordinates as normal (x, y) 

  // give the view window an origin at -180m, -150m
  // size is a 4x3 ratio
  // VTM = T(0, rows-1)S(cols/vx, rows/vy)T(180, 150)
  matrix_translate2D(&VTM, 120, 100);
  matrix_scale2D(&VTM, cols/(4*60), -rows/(3*60));
  matrix_translate2D(&VTM, 0, rows-1);
  printf("VTM\n");
  matrix_print(&VTM, stdout);

  // make a space sun oriented along the positive X axis
  // use the LTM to move simple primitives into place
  // use the GTM to rotate the sun
  // use the VTM to change the view

  // make a list of points that form the unit circle
  for(i=0;i<Resolution;i++) {
    point_set2D(&(unitCircle[i]), 
    cos( i * 2.0 * M_PI / (float)Resolution), 
    sin( i * 2.0 * M_PI / (float)Resolution));
  }

  point_set2D(&(unitTriangle[0]), 0, 0);
  point_set2D(&(unitTriangle[1]), 1, 0);
  point_set2D(&(unitTriangle[2]), 0, 1);

  // build a set of polygons that form the sun in model space
  // put the origin of the model between the engines

  // outline for the sun
  matrix_identity(&LTM);
  matrix_scale2D(&LTM, 31, 31);
  // move it 20m along the X-axis
  matrix_translate2D(&LTM, 20, 0);
  // transform the circle points using LTM
  for(i=0;i<Resolution;i++) {
    matrix_xformPoint(&LTM, &(unitCircle[i]), &(pt[i]));
  }

  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(Resolution, pt);
  color[index++] = Yellow;

  // Sun rays
  matrix_identity(&LTM);
  matrix_translate2D(&LTM, -0.5, -0.5);
  matrix_scale2D(&LTM, 25, 25);
  matrix_rotateZ( &LTM, 0.5, -0.86 );
  for(i=0;i<3;i++) {
    matrix_xformPoint(&LTM, &(unitTriangle[i]), &(pt[i]));
  }
  
  // Top left ray
  matrix_identity(&LTM);
  matrix_translate2D(&LTM, -15, 12);
  for(i=0;i<3;i++) 
    matrix_xformPoint(&LTM, &(pt[i]), &(ptt[i]));
  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(3, ptt);
  color[index++] = Yellow_White;

  // Left bottom ray
  matrix_identity(&LTM);
  matrix_rotateZ( &LTM, 0.34, 0.93 );
  matrix_translate2D(&LTM, 0, -30);
  for(i=0;i<3;i++) 
    matrix_xformPoint(&LTM, &(pt[i]), &(ptt[i]));
  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(3, ptt);
  color[index++] = Yellow2;

  // Right bottom ray
  matrix_identity(&LTM);
  matrix_rotateZ( &LTM, -0.71, 0.71 );
  matrix_translate2D(&LTM, 42, -30);
  for(i=0;i<3;i++) 
    matrix_xformPoint(&LTM, &(pt[i]), &(ptt[i]));
  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(3, ptt);
  color[index++] = Yellow_White;

 // Top right ray
  matrix_identity(&LTM);
  matrix_rotateZ( &LTM, -0.94, -0.34 );
  matrix_translate2D(&LTM, 56, 5);
  for(i=0;i<3;i++) 
    matrix_xformPoint(&LTM, &(pt[i]), &(ptt[i]));
  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(3, ptt);
  color[index++] = Yellow2;

  // Top most ray
  matrix_identity(&LTM);
  matrix_rotateZ( &LTM, 0.26, -0.97 );
  matrix_translate2D(&LTM, 24, 35);
  for(i=0;i<3;i++) 
    matrix_xformPoint(&LTM, &(pt[i]), &(ptt[i]));
  // add the polygon
  matrix_print(&LTM, stdout);
  sun[index] = polygon_createp(3, ptt);
  color[index++] = Yellow;

  matrix_print(&GTM, stdout);
  matrix_rotateZ(&GTM, cos(theta*M_PI/180.0), sin(theta*M_PI/180.0));
	
  printf("GTM: here\n");
  matrix_print(&GTM, stdout);

  printf("Pre-GTM/VTM\n");
  polygon_print(sun[0], stdout);

  for(i=0;i<index;i++) {

    // multiply the polygon by the global transform matrix
    matrix_xformPolygon(&GTM, sun[i]);
    if(i==0) {
      printf("Pre-VTM\n");
      polygon_print(sun[i], stdout);
    }

    // multiply the polygon by the view transformation matrix
    matrix_xformPolygon(&VTM, sun[i]);

    if(i==0) {
      printf("Pre-draw\n");
      polygon_print(sun[i], stdout);
    }

    // draw the polygon
    polygon_drawFill(sun[i], src, color[i]);
  }

  image_write(src, "rotating_sun.ppm");

  image_free(src);

	return(0); 
}