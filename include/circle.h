#ifndef CIRCLE_H

#define CIRCLE_H

#include "image.h"
#include "color.h"

typedef struct {
  double r;
  Point c;
} Circle;

typedef struct {
  double ra; // major axis radius
  double rb; //minor axis radius
  Point c; // center
//  double a; // angle of major axis relative to the X-axis
} Ellipse;

void circle_set( Circle *circ, Point pt, int radius );

void circle_draw( Circle *circ, Image *src, Color color );

void circle_draw_dashed( Circle *circ, Image *src, Color color, int interval );

void circle_drawFill(Circle *c, Image *src, Color p);

void circle_drawGradientFill(Circle *circ, Image *src, int x_offset, int y_offset, Color color1, Color color2);

void colorHorizontalGradient(Image *src, int x_anchor, int y_anchor, int x0, int x1, int y, int radius, Color color1, Color color2);

void colorHorizontal(Image *src, int x0, int x1, int y, Color color);

// initialize an ellipse to location tc and radii ta and tb.
void ellipse_set(Ellipse *e, Point tc, double ta, double tb);

// draw into src using color p.
void ellipse_draw(Ellipse *e, Image *src, Color p);

void ellipse_draw_dashed(Ellipse *e, Image *src, Color color, int interval);

//  draw a filled ellipse into src using color p.
void ellipse_drawFill(Ellipse *e, Image *src, Color p);

#endif