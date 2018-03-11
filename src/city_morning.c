/*
  Assignment 4, required image 1

  C version
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

/*
  Program to test polygon functionality
*/
int main(int argc, char *argv[]) {
  Image *src;
  const int rows = 1000;
  const int cols = 1000;

  Color Red, Dark_Red, Orange, Yellow, Light_Yellow, White, Blue, Gray2, Gray3, Gray4, Gray5, Gray8, Gray9, Light_Black, Black;
 
  Point tri[3];
  Point rect[4];

  srand(42);

  color_set(&Red, 1.0, 0.0, 0.1 );
  color_set(&Dark_Red, 0.6, 0.2, 0.1 );
  color_set(&Orange, 1.0, 0.6, 0.3 );
  color_set(&White, 1.0, 1.0, 1.0 );
  color_set(&Blue, 0.2, 0.1, 0.95 );
  color_set(&Yellow, 1.0, 1.0, 0.0 );
  color_set(&Light_Yellow, 1.0, 1.0, 0.9 );
  color_set(&Gray2, 0.2, 0.2, 0.2 );
  color_set(&Gray3, 0.3, 0.3, 0.3 );
  color_set(&Gray4, 0.4, 0.4, 0.4 );
  color_set(&Gray5, 0.5, 0.5, 0.5 );
  color_set(&Gray8, 0.8, 0.8, 0.8 );
  color_set(&Gray9, 0.90, 0.90, 0.90 );
  color_set(&Black, 0.0, 0.0, 0.0 );
  color_set(&Light_Black, 0.1, 0.1, 0.1 );

  printf("Writing city morning scene\n");
  src = image_create(rows, cols, 255);

  Polygon *triangle;
  // Background
  point_set2D(&(tri[0]), 0, 0);
  point_set2D(&(tri[1]), 1000, 0);
  point_set2D(&(tri[2]), 0, 1000);
  triangle = polygon_createp(3, tri);
  polygon_drawFillBGradient( triangle, src, Red, Orange, Dark_Red);

  point_set2D(&(tri[0]), 1000, 0);
  point_set2D(&(tri[1]), 1000, 1000);
  point_set2D(&(tri[2]), 0, 1000);
  triangle = polygon_createp(3, tri);
  polygon_drawFillBGradient( triangle, src, Orange, Red, Dark_Red);

  // Sun
  Circle circle;
  Point p_circle;
  point_set2D( &p_circle, 200, 200 );
  circle_set( &circle, p_circle, 100 );
  circle_drawGradientFill( &circle, src, 10, 10, Light_Yellow, Yellow);

  // Road
  Polygon *points_4; 
  point_set2D(&(rect[0]), 0, 900);
  point_set2D(&(rect[1]), 1000, 900);
  point_set2D(&(rect[2]), 1000, 1000);
  point_set2D(&(rect[3]), 0, 1000);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Light_Black); 

  // Building behind road
  point_set2D(&(rect[0]), 700, 500);
  point_set2D(&(rect[1]), 850, 500);
  point_set2D(&(rect[2]), 850, 900);
  point_set2D(&(rect[3]), 700, 900);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray5); // Front

  point_set2D(&(rect[0]), 700, 500);
  point_set2D(&(rect[1]), 850, 500);
  point_set2D(&(rect[2]), 880, 490);
  point_set2D(&(rect[3]), 730, 490);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray9); // Top

  point_set2D(&(rect[0]), 850, 500);
  point_set2D(&(rect[1]), 880, 490);
  point_set2D(&(rect[2]), 880, 890);
  point_set2D(&(rect[3]), 850, 900);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray3); // Side

  // for ( int i = 605 ; i < 830; i += 40 ) { // Window
  //   for ( int j = 805 ; j < 1000; j += 35 ) {
  //     point_set2D(&(rect[0]), i, j);
  //     point_set2D(&(rect[1]), i+30, j);
  //     point_set2D(&(rect[2]), i+30, j+22);
  //     point_set2D(&(rect[3]), i, j+22);
  //     points_4 = polygon_createp(4, rect);
  //     float f = (rand() % 100);
  //     if ( f > 20 ) 
  //       polygon_drawFill(points_4, src, Gray2); 
  //   }
  // }

  // Building left
  point_set2D(&(rect[0]), 200, 710);
  point_set2D(&(rect[1]), 350, 710);
  point_set2D(&(rect[2]), 350, 1000);
  point_set2D(&(rect[3]), 200, 1000);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray5); // Front

  point_set2D(&(rect[0]), 250, 680);
  point_set2D(&(rect[1]), 400, 680);
  point_set2D(&(rect[2]), 350, 710);
  point_set2D(&(rect[3]), 200, 710);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray9); // Top

  point_set2D(&(rect[0]), 350, 710);
  point_set2D(&(rect[1]), 400, 680);
  point_set2D(&(rect[2]), 400, 1000);
  point_set2D(&(rect[3]), 350, 1000);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray3); // Side

  for ( int i = 210 ; i < 330; i += 25 ) { // Window
    for ( int j = 720 ; j < 1000; j += 30 ) {
      point_set2D(&(rect[0]), i, j);
      point_set2D(&(rect[1]), i+20, j);
      point_set2D(&(rect[2]), i+20, j+20);
      point_set2D(&(rect[3]), i, j+20);
      points_4 = polygon_createp(4, rect);
      float f = (rand() % 100);
      if ( f > 20 ) 
        polygon_drawFill(points_4, src, Gray2); 
    }
  }

  // Building right
  point_set2D(&(rect[0]), 600, 800);
  point_set2D(&(rect[1]), 850, 800);
  point_set2D(&(rect[2]), 850, 1000);
  point_set2D(&(rect[3]), 600, 1000);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray5); // Front

  point_set2D(&(rect[0]), 630, 780);
  point_set2D(&(rect[1]), 880, 780);
  point_set2D(&(rect[2]), 850, 800);
  point_set2D(&(rect[3]), 600, 800);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray9); // Top

  point_set2D(&(rect[0]), 850, 800);
  point_set2D(&(rect[1]), 880, 780);
  point_set2D(&(rect[2]), 880, 1000);
  point_set2D(&(rect[3]), 850, 1000);
  points_4 = polygon_createp(4, rect);
  polygon_drawFill(points_4, src, Gray3); // Side

  for ( int i = 605 ; i < 830; i += 40 ) { // Window
    for ( int j = 805 ; j < 1000; j += 35 ) {
      point_set2D(&(rect[0]), i, j);
      point_set2D(&(rect[1]), i+30, j);
      point_set2D(&(rect[2]), i+30, j+22);
      point_set2D(&(rect[3]), i, j+22);
      points_4 = polygon_createp(4, rect);
      float f = (rand() % 100);
      if ( f > 20 ) 
        polygon_drawFill(points_4, src, Gray2); 
    }
  }

  image_write(src, "city_morning.ppm");
  image_free(src);



  return(0);
}
