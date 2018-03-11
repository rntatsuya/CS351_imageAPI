/*
  Assignment 4, required image 1

  C version
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main(int argc, char *argv[]) {
  Image *src;

  const int rows = 1000;
  const int cols = 1000;
  
  Color Red, Orange, Yellow, White, Blue, Dark_Gray, Dark_Gray2, Light_Gray, Gray, Light_Black, Black;

  Point tri[3];
  Point rect[4];

  srand(42);

  color_set(&Red, 0.9, 0.2, 0.1 );
  color_set(&Orange, 0.95, 0.7, 0.3 );
  color_set(&White, 1.0, 1.0, 1.0 );
  color_set(&Blue, 0.2, 0.1, 0.95 );
  color_set(&Dark_Gray, 0.3, 0.3, 0.3 );
  color_set(&Gray, 0.5, 0.5, 0.5 );
  color_set(&Yellow, 1.0, 1.0, 0.0 );
  color_set(&Light_Gray, 0.90, 0.90, 0.90 );
  color_set(&Black, 0.0, 0.0, 0.0 );
  color_set(&Light_Black, 0.1, 0.1, 0.1 );
  color_set(&Dark_Gray2, 0.2, 0.2, 0.2 );

  printf("Writing night scene\n");
  src = image_create(rows, cols, 255);

  Polygon *triangle;
  // Background
  point_set2D(&(tri[0]), 0, 0);
  point_set2D(&(tri[1]), 1000, 0);
  point_set2D(&(tri[2]), 0, 1000);
  triangle = polygon_createp(3, tri);
  polygon_drawFillBGradient( triangle, src, Light_Black, Blue, Black);

  point_set2D(&(tri[0]), 1000, 0);
  point_set2D(&(tri[1]), 1000, 1000);
  point_set2D(&(tri[2]), 0, 1000);
  triangle = polygon_createp(3, tri);
  polygon_drawFillBGradient( triangle, src, Blue, Light_Black, Black);

  // Moon
  Circle circle;
  Point p_circle;
  point_set2D( &p_circle, 800, 200 );
  circle_set( &circle, p_circle, 100 );
  circle_drawGradientFill( &circle, src, -30, 30, Light_Gray, Gray);

  // Building Left
  Polygon *building; 
  point_set2D(&(rect[0]), 200, 710);
  point_set2D(&(rect[1]), 350, 710);
  point_set2D(&(rect[2]), 350, 1000);
  point_set2D(&(rect[3]), 200, 1000);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Dark_Gray2); // Front

  point_set2D(&(rect[0]), 250, 680);
  point_set2D(&(rect[1]), 400, 680);
  point_set2D(&(rect[2]), 350, 710);
  point_set2D(&(rect[3]), 200, 710);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Dark_Gray); // Top

  point_set2D(&(rect[0]), 350, 710);
  point_set2D(&(rect[1]), 400, 680);
  point_set2D(&(rect[2]), 400, 1000);
  point_set2D(&(rect[3]), 350, 1000);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Light_Black); // Side

  for ( int i = 205 ; i < 340; i += 25 ) { // Window
    for ( int j = 720 ; j < 1000; j += 30 ) {
      point_set2D(&(rect[0]), i, j);
      point_set2D(&(rect[1]), i+20, j);
      point_set2D(&(rect[2]), i+20, j+20);
      point_set2D(&(rect[3]), i, j+20);
      building = polygon_createp(4, rect);
      float f = (rand() % 100);
      if ( f > 50 ) {
        polygon_drawFill(building, src, Yellow); 
      }
    }
  }

  // Building Right
  point_set2D(&(rect[0]), 600, 800);
  point_set2D(&(rect[1]), 850, 800);
  point_set2D(&(rect[2]), 850, 1000);
  point_set2D(&(rect[3]), 600, 1000);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Dark_Gray2); // Front

  point_set2D(&(rect[0]), 630, 780);
  point_set2D(&(rect[1]), 880, 780);
  point_set2D(&(rect[2]), 850, 800);
  point_set2D(&(rect[3]), 600, 800);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Dark_Gray); // Top

  point_set2D(&(rect[0]), 850, 800);
  point_set2D(&(rect[1]), 880, 780);
  point_set2D(&(rect[2]), 880, 1000);
  point_set2D(&(rect[3]), 850, 1000);
  building = polygon_createp(4, rect);
  polygon_drawFill(building, src, Light_Black); // Side

  for ( int i = 605 ; i < 830; i += 40 ) { // Window
    for ( int j = 805 ; j < 1000; j += 35 ) {
      point_set2D(&(rect[0]), i, j);
      point_set2D(&(rect[1]), i+20, j);
      point_set2D(&(rect[2]), i+20, j+20);
      point_set2D(&(rect[3]), i, j+20);
      building = polygon_createp(4, rect);
      float f = (rand() % 100);
      if ( f > 50 ) {
        polygon_drawFill(building, src, Yellow); 
      }
    }
  }

  image_write(src, "night.ppm");
  image_free(src);

  return(0);
}
