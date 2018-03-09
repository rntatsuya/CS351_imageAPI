/*
 * Tatsuya Yokota
 * circle.c
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "color.h"
#include "image.h"
#include "line.h"
#include "circle.h"

// – initialize to center and radius.
void circle_set( Circle *circ, Point pt, int radius ) {
  circ->r = radius;
  circ->c = pt;
}

// – draw the circle into src using color p.
// base code from Baker textbook
void circle_draw( Circle *circ, Image *src, Color color ) {
  int xCenter = circ->c.val[0];
  int yCenter = circ->c.val[1];
  int x = 0;
  int y = -circ->r;
  int p = 1 - circ->r;
  
//   printf("%d, %d\n", yCenter + y, xCenter + x);
//   printf("%d, %d\n", yCenter + y, xCenter - x);
//   printf("%d, %d\n", yCenter - y, xCenter + x);
//   printf("%d, %d\n", yCenter - y, xCenter - x);
//   printf("%d, %d\n", yCenter + x, xCenter + y);
//   printf("%d, %d\n", yCenter + x, xCenter - y);
//   printf("%d, %d\n", yCenter - x, xCenter + y);
//   printf("%d, %d\n", yCenter - x, xCenter - y);
  // Plot first set of points
  image_setColor(src, yCenter + y, xCenter + x, color);
  image_setColor(src, yCenter + y, xCenter - x, color);
  image_setColor(src, yCenter - y, xCenter + x, color);
  image_setColor(src, yCenter - y, xCenter - x, color);
  image_setColor(src, yCenter + x, xCenter + y, color);
  image_setColor(src, yCenter + x, xCenter - y, color);
  image_setColor(src, yCenter - x, xCenter + y, color);
  image_setColor(src, yCenter - x, xCenter - y, color);
  
  
  while (x > y) {
    x--;
    if (p < 0) 
      p += 1 - 2*x;
    else {
      y++;
      p += 1 - 2*(x - y);
    }

    image_setColor(src, yCenter + y, xCenter + x, color);
    image_setColor(src, yCenter + y, xCenter - x, color);
    image_setColor(src, yCenter - y, xCenter + x, color);
    image_setColor(src, yCenter - y, xCenter - x, color);
    image_setColor(src, yCenter + x, xCenter + y, color);
    image_setColor(src, yCenter + x, xCenter - y, color);
    image_setColor(src, yCenter - x, xCenter + y, color);
    image_setColor(src, yCenter - x, xCenter - y, color);
  }
}

// draw a dashed circle with a given interval 
void circle_draw_dashed( Circle *circ, Image *src, Color color, int interval ) {
  int xCenter = circ->c.val[0];
  int yCenter = circ->c.val[1];
  int x = 0;
  int y = -circ->r;
  int p = 1 - circ->r;
  int counter = 0;

  // Plot first set of points
  image_setColor(src, yCenter + y, xCenter + x, color);
  image_setColor(src, yCenter + y, xCenter - x, color);
  image_setColor(src, yCenter - y, xCenter + x, color);
  image_setColor(src, yCenter - y, xCenter - x, color);
  image_setColor(src, yCenter + x, xCenter + y, color);
  image_setColor(src, yCenter + x, xCenter - y, color);
  image_setColor(src, yCenter - x, xCenter + y, color);
  image_setColor(src, yCenter - x, xCenter - y, color);
  
  
  while (x > y) {
    x--;
    if (p < 0) 
      p += 1 - 2*x;
    else {
      y++;
      p += 1 - 2*(x - y);
    }
    if (!(counter % interval)) {       
      image_setColor(src, yCenter + y, xCenter + x, color);
      image_setColor(src, yCenter + y, xCenter - x, color);
      image_setColor(src, yCenter - y, xCenter + x, color);
      image_setColor(src, yCenter - y, xCenter - x, color);
      image_setColor(src, yCenter + x, xCenter + y, color);
      image_setColor(src, yCenter + x, xCenter - y, color);
      image_setColor(src, yCenter - x, xCenter + y, color);
      image_setColor(src, yCenter - x, xCenter - y, color);
    }
    counter++;
  }
}


// draw a radiantly filled circle into src using color p.
void circle_drawFill(Circle *circ, Image *src, Color color) {
  int xCenter = circ->c.val[0];
  int yCenter = circ->c.val[1];
  int x = 0;
  int y = -circ->r;
  int p = 1 - circ->r;

  // Plot first set of points
  colorHorizontal(src, xCenter + x, xCenter - x, yCenter + y, color);  
  colorHorizontal(src, xCenter + x, xCenter - x, yCenter - y, color);
  colorHorizontal(src, xCenter + y, xCenter - y, yCenter + x, color);  
  colorHorizontal(src, xCenter + y, xCenter - y, yCenter - x, color);  
  
  while (x > y) {
    x--;
    if (p < 0) 
      p += 1 - 2*x;
    else {
      y++;
      p += 1 - 2*(x - y);
    }

    colorHorizontal(src, xCenter + x, xCenter - x, yCenter + y, color);  
    colorHorizontal(src, xCenter + x, xCenter - x, yCenter - y, color);
    colorHorizontal(src, xCenter + y, xCenter - y, yCenter + x, color);  
    colorHorizontal(src, xCenter + y, xCenter - y, yCenter - x, color); 
  }
}

// draw a filled circle into src using color p.
void circle_drawGradientFill(Circle *circ, Image *src, int x_offset, int y_offset, Color color1, Color color2) {
  int xCenter = circ->c.val[0];
  int yCenter = circ->c.val[1];
  int x = 0;
  int y = -circ->r;
  int p = 1 - circ->r;

  // Plot first set of points
  colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + x, xCenter - x, yCenter + y, circ->r, color1, color2);
  colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + x, xCenter - x, yCenter - y, circ->r, color1, color2);
  colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + y, xCenter - y, yCenter + x, circ->r, color1, color2);
  colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + y, xCenter - y, yCenter - x, circ->r, color1, color2);
  
  while (x > y) {
    x--;
    if (p < 0) 
      p += 1 - 2*x;
    else {
      y++;
      p += 1 - 2*(x - y);
    }

    colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + x, xCenter - x, yCenter + y, circ->r, color1, color2);
    colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + x, xCenter - x, yCenter - y, circ->r, color1, color2);
    colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + y, xCenter - y, yCenter + x, circ->r, color1, color2);
    colorHorizontalGradient(src, xCenter+x_offset, yCenter+y_offset, xCenter + y, xCenter - y, yCenter - x, circ->r, color1, color2);
  }
}

// color horizontally from Point a to b
void colorHorizontal(Image *src, int x0, int x1, int y, Color color) {
  int dx;
  int c0;
  int c1;
  int i;
  
  // force draw from left to right
  if (x0 < x1) {
    c0 = x0;
    c1 = x1;
  }
  else {
    c1 = x0;
    c0 = x1;
  }
  // always positive
  dx = c1 - c0;
  
  for (i=0; i<dx; i++) {
    image_setColor(src, y, c0 + i, color);
  }
}

// color horizontally in a gradient
void colorHorizontalGradient(Image *src, int x_anchor, int y_anchor, int x0, int x1, int y, int radius, Color color1, Color color2) {
  int dx;
  int c0;
  int c1;
  int i;
  
  // force draw from left to right
  if (x0 < x1) {
    c0 = x0;
    c1 = x1;
  }
  else {
    c1 = x0;
    c0 = x1;
  }
  // always positive
  dx = c1 - c0;
  
  for (i=0; i<dx; i++) {
    image_setColorGradient(src, y_anchor, x_anchor, y, c0+i, radius, color1, color2);
  }
}


// initialize an ellipse to location tc and radii ta and tb.
void ellipse_set(Ellipse *e, Point tc, double ta, double tb) {
  e->ra = ta;
  e->rb = tb;
  e->c = tc;
}



// draw into src using color p.
// base code from Baker textbook
void ellipse_draw(Ellipse *e, Image *src, Color color) {
  int xCenter = e->c.val[0];
  int yCenter = e->c.val[1];
  int p;
  int x = 0;
  int y = -e->rb;
  int Rx2 = e->ra * e->ra;
  int Ry2 = e->rb * e->rb;
  int twoRx2 = 2*Rx2;
  int twoRy2 = 2*Ry2;
  int px = twoRy2;
  int py = twoRx2 * -y;
  
  
  /* Plot the first set of points */
  image_setColor(src, yCenter + y, xCenter + x, color); 
  image_setColor(src, yCenter + y, xCenter - x, color); 
  image_setColor(src, yCenter - y, xCenter + x, color); 
  image_setColor(src, yCenter - y, xCenter - x, color);
  
  /* Region 1 */
  p = Ry2 - (Rx2 * -y) + (0.25 * Rx2) + Ry2 + px;
  while (px < py) {
    x--;
    px += twoRy2;
    if (p < 0)
      p += Ry2 + px;
    else {
      y++;
      py -= twoRx2;
      p += Ry2 + px - py;
    }
    image_setColor(src, yCenter + y, xCenter + x, color); 
    image_setColor(src, yCenter + y, xCenter - x, color); 
    image_setColor(src, yCenter - y, xCenter + x, color); 
    image_setColor(src, yCenter - y, xCenter - x, color);
  }
  
  /* Region 2 */
  p = Ry2*(x*x + x) + Rx2*(y*y - 2*y + 1) - Rx2*Ry2 + Rx2 - py;
  while (y < 0) {
    y++;
    py -= twoRx2;
    if (p > 0) 
      p += Rx2 - py;
    else {
      x--;
      px += twoRy2;
      p += Rx2 - py + px;
    }
    image_setColor(src, yCenter + y, xCenter + x, color); 
    image_setColor(src, yCenter + y, xCenter - x, color); 
    image_setColor(src, yCenter - y, xCenter + x, color); 
    image_setColor(src, yCenter - y, xCenter - x, color);
  }
}

// draw a dashed ellipse
void ellipse_draw_dashed(Ellipse *e, Image *src, Color color, int interval) {
  int xCenter = e->c.val[0];
  int yCenter = e->c.val[1];
  int p;
  int x = 0;
  int y = -e->rb;
  int Rx2 = e->ra * e->ra;
  int Ry2 = e->rb * e->rb;
  int twoRx2 = 2*Rx2;
  int twoRy2 = 2*Ry2;
  int px = twoRy2;
  int py = twoRx2 * -y;
  int counter = 0; 
  
  
  /* Plot the first set of points */
  image_setColor(src, yCenter + y, xCenter + x, color); 
  image_setColor(src, yCenter + y, xCenter - x, color); 
  image_setColor(src, yCenter - y, xCenter + x, color); 
  image_setColor(src, yCenter - y, xCenter - x, color);
  
  /* Region 1 */
  p = Ry2 - (Rx2 * -y) + (0.25 * Rx2) + Ry2 + px;
  while (px < py) {
    x--;
    px += twoRy2;
    if (p < 0)
      p += Ry2 + px;
    else {
      y++;
      py -= twoRx2;
      p += Ry2 + px - py;
    }
    if (!(counter % interval)) {       
      image_setColor(src, yCenter + y, xCenter + x, color); 
      image_setColor(src, yCenter + y, xCenter - x, color); 
      image_setColor(src, yCenter - y, xCenter + x, color); 
      image_setColor(src, yCenter - y, xCenter - x, color);
    }
    counter++;
  }
  
  // reset counter for second region
  counter = 0;
  /* Region 2 */
  p = Ry2*(x*x + x) + Rx2*(y*y - 2*y + 1) - Rx2*Ry2 + Rx2 - py;
  while (y < 0) {
    y++;
    py -= twoRx2;
    if (p > 0) 
      p += Rx2 - py;
    else {
      x--;
      px += twoRy2;
      p += Rx2 - py + px;
    }
    if (!(counter % interval)) {       
      image_setColor(src, yCenter + y, xCenter + x, color); 
      image_setColor(src, yCenter + y, xCenter - x, color); 
      image_setColor(src, yCenter - y, xCenter + x, color); 
      image_setColor(src, yCenter - y, xCenter - x, color);
    }
    counter++;
  }
}

//  draw a filled ellipse into src using color p.
void ellipse_drawFill(Ellipse *e, Image *src, Color color){ 
  int xCenter = e->c.val[0];
  int yCenter = e->c.val[1];
  int p;
  int x = 0;
  int y = -e->rb;
  int Rx2 = e->ra * e->ra;
  int Ry2 = e->rb * e->rb;
  int twoRx2 = 2*Rx2;
  int twoRy2 = 2*Ry2;
  int px = twoRy2;
  int py = twoRx2 * -y;
  
  
  /* Plot the first set of points */
  colorHorizontal(src, xCenter + x, xCenter - x, yCenter + y, color);  
  colorHorizontal(src, xCenter + x, xCenter - x, yCenter - y, color);
  
  /* Region 1 */
  p = Ry2 - (Rx2 * -y) + (0.25 * Rx2) + Ry2 + px;
  while (px < py) {
    x--;
    px += twoRy2;
    if (p < 0)
      p += Ry2 + px;
    else {
      y++;
      py -= twoRx2;
      p += Ry2 + px - py;
    }
    colorHorizontal(src, xCenter + x, xCenter - x, yCenter + y, color);  
    colorHorizontal(src, xCenter + x, xCenter - x, yCenter - y, color);
  }
  
  /* Region 2 */
  p = Ry2*(x*x + x) + Rx2*(y*y - 2*y + 1) - Rx2*Ry2 + Rx2 - py;
  while (y < 0) {
    y++;
    py -= twoRx2;
    if (p > 0) 
      p += Rx2 - py;
    else {
      x--;
      px += twoRy2;
      p += Rx2 - py + px;
    }
    colorHorizontal(src, xCenter + x, xCenter - x, yCenter + y, color);  
    colorHorizontal(src, xCenter + x, xCenter - x, yCenter - y, color);
  }
}
























