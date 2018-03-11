#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graphics.h"

int main( int argc, char *argv[] ) {

	Image *src;
	int rows = 700;
	int cols = 1000;
	src = image_create( rows, cols, 255 );

	Color Brown;
	Color Dark_Brown;
	Color Light_Brown;
	Color VDark_Gray;
	Color Light_Gray;
	Color Dark_Gray;
	Color Light_Black;
	color_set(&Brown, 0.87, 0.72, 0.53 );
	color_set(&Dark_Brown, 0.82, 0.71, 0.55 );
	color_set(&Light_Brown, 0.96, 0.87, 0.70 );
	color_set(&Light_Gray, 0.83, 0.83, 0.83 );
	color_set(&VDark_Gray, 0.30, 0.30, 0.30 );
	color_set(&Dark_Gray, 0.66, 0.66, 0.66 );
	color_set(&Light_Black, 0.05, 0.05, 0.05 );
	
	Point pt[100]; // Array of points

	// Front of desk 
	Polygon *front_desk; 
	point_set2D(&(pt[0]), 250, 500);
	point_set2D(&(pt[1]), 750, 500);
	point_set2D(&(pt[2]), 750, 550);
	point_set2D(&(pt[3]), 250, 550);
	front_desk = polygon_createp(4, pt);
	polygon_drawFill(front_desk, src, Brown);

	// Legs of desk
	Polygon *left_leg; 
	point_set2D(&(pt[0]), 250, 550);
	point_set2D(&(pt[1]), 280, 550);
	point_set2D(&(pt[2]), 280, 1000);
	point_set2D(&(pt[3]), 250, 1000);
	left_leg = polygon_createp(4, pt);
	polygon_drawFill(left_leg, src, Dark_Brown);
	
	Polygon *right_leg; 
	point_set2D(&(pt[0]), 720, 550);
	point_set2D(&(pt[1]), 750, 550);
	point_set2D(&(pt[2]), 750, 1000);
	point_set2D(&(pt[3]), 720, 1000);
	right_leg = polygon_createp(4, pt);
	polygon_drawFill(right_leg, src, Dark_Brown);

	// Surface of desk 
	Polygon *surface;
	point_set2D(&(pt[0]), 250, 500);
	point_set2D(&(pt[1]), 750, 500);
	point_set2D(&(pt[2]), 700, 370);
	point_set2D(&(pt[3]), 300, 370);
	surface = polygon_createp(4, pt);
	polygon_drawFill(surface, src, Light_Brown);

	// Mac laptop  
	Polygon *mac_top;
	point_set2D(&(pt[0]), 450, 290);
	point_set2D(&(pt[1]), 600, 290);
	point_set2D(&(pt[2]), 600, 390);
	point_set2D(&(pt[3]), 450, 390);
	mac_top = polygon_createp(4, pt);
	polygon_drawFill(mac_top, src, Light_Gray);

	Polygon *mac_screen;
	point_set2D(&(pt[0]), 455, 295);
	point_set2D(&(pt[1]), 595, 295);
	point_set2D(&(pt[2]), 595, 385);
	point_set2D(&(pt[3]), 455, 385);
	mac_screen = polygon_createp(4, pt);
	polygon_drawFill(mac_screen, src, Light_Black);

	Polygon *mac_bottom;
	point_set2D(&(pt[0]), 450, 390);
	point_set2D(&(pt[1]), 600, 390);
	point_set2D(&(pt[2]), 625, 430);
	point_set2D(&(pt[3]), 425, 430);
	mac_bottom = polygon_createp(4, pt);
	polygon_drawFill(mac_bottom, src, Dark_Gray);

	// Coffee cup 
	Ellipse coffee_cup;
	Point coffee_center;
 	point_set2D( &coffee_center, 340, 400 );
	ellipse_set( &coffee_cup, coffee_center, 20, 10 );
	ellipse_drawFill( &coffee_cup, src, Dark_Gray );

	Polygon *coffee_rect;
	point_set2D(&(pt[0]), 310, 350);
	point_set2D(&(pt[1]), 370, 350);
	point_set2D(&(pt[2]), 360, 400);
	point_set2D(&(pt[3]), 320, 400);
	coffee_rect = polygon_createp(4, pt);
	polygon_drawFill(coffee_rect, src, Dark_Gray);
	
	Ellipse top_cup;
 	point_set2D( &coffee_center, 340, 350 );
	ellipse_set( &top_cup, coffee_center, 30, 10 );
	ellipse_drawFill( &top_cup, src, Light_Gray );

	image_write( src, "desk.ppm" );
	image_free(src);
}