/*
 * Tatsuya Yokota
 * line.c
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "color.h"
#include "image.h"
#include "line.h"

// set the first two values of the vector to x and y. 
// Set the third value to 0.0 and the fourth value to 1.0
Point point_create2D(double x, double y) {
  Point point;
  
  point.val[0] = x;
  point.val[1] = y;
  point.val[2] = 0.0;  
  point.val[3] = 1.0;
    
  return point;
}

// set the first two values of the vector to x and y. 
// Set the third value to 0.0 and the fourth value to 1.0
void point_set2D(Point *point, double x, double y) {
  point->val[0] = x;
  point->val[1] = y;
  point->val[2] = 0.0;
  point->val[3] = 1.0;
}

// – set the point’s values to x and y and z. Set the homogeneous coordinate to 1.0.
void point_set3D(Point *point, double x, double y, double z) {
  point->val[0] = x;
  point->val[1] = y;
  point->val[2] = z;
  point->val[3] = 1.0;
}

void point_setFraction(Point *point, Point *p1, Point *p2, float u) {
//   printf("Taking fraction %.2f of: \n", u);
//   point_print(p1, stdout);
//   point_print(p2, stdout);
  point_set3D(point, (p1->val[0]+p2->val[0])*u,  (p1->val[1]+p2->val[1])*u, (p1->val[2]+p2->val[2])*u);
//   printf("Got\n");
//   point_print(point, stdout);
}

// set the four values of the vector to x, y, z, and h, respectively.
void point_set(Point *point, double x, double y, double z, double h) {
  point->val[0] = x;
  point->val[1] = y;
  point->val[2] = z;
  point->val[3] = h;
}

// normalize the x and y values of a point by its homogeneous coordinate: x = x/h, y = y/h
void point_normalize(Point *point) {
  point->val[0] /= point->val[3];
  point->val[1] /= point->val[3];
}

//  copy the point data structure.
void point_copy(Point *to, Point *from) {
  to->val[0] = from->val[0];
  to->val[1] = from->val[1];
  to->val[2] = from->val[2];
  to->val[3] = from->val[3];
}

//  copy the point data structure.
void point_draw(Point *p, Image *src, Color color) {
  int x = (int)p->val[0];
  int y = (int)p->val[1];
  src->data[y*src->cols + x].rgb[0] = color.c[0];
  src->data[y*src->cols + x].rgb[1] = color.c[1];
  src->data[y*src->cols + x].rgb[2] = color.c[2];
}

// draw the p into src using FPixel c.
void point_drawf(Point *p, Image *src, FPixel c) {
  int x = (int)p->val[0];
  int y = (int)p->val[1];
  src->data[y*src->cols + x].rgb[0] = c.rgb[0];
  src->data[y*src->cols + x].rgb[1] = c.rgb[1];
  src->data[y*src->cols + x].rgb[2] = c.rgb[2];
}

// – use fprintf to print the contents of the Point to the stream fp
void point_print(Point *point, FILE *fp) {  
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file!\n");
    exit(1);
  }
    
  fprintf(fp, "(x, y, z, h): (%lf, %lf, %lf, %lf)\n", 
  point->val[0],
  point->val[1],
  point->val[2],
  point->val[3]);
}

// – initialize a 2D line
void line_set2D(Line *line, double x1, double y1, double x2, double y2) {
  Point start;
  Point end;

  start.val[0] = x1;
  start.val[1] = y1;
  start.val[2] = 0.0;
  start.val[3] = 1.0;

  end.val[0] = x2;
  end.val[1] = y2;
  end.val[2] = 0.0;
  end.val[3] = 1.0;
  
  line->a = start;
  line->b = end;
  line->zBuffer = 1.0;
} // end of line_set

//  initialize a line to ta and tb.
// void line_set(Line *line, Point start, Point end) {
//   line->a = start;
//   line->b = end;
// } // end of line_set

// – set the z-buffer flag to the given value.
void line_zBuffer(Line *l, int flag) {
  l->zBuffer = flag;
}

// – normalize the x and y values of the endpoints by their homogeneous coordinate
void line_normalize(Line *l) {
  l->a.val[0] /= l->a.val[3];
  l->a.val[1] /= l->a.val[3];
  l->b.val[0] /= l->b.val[3];
  l->b.val[1] /= l->b.val[3];
}

// – copy the line data structure.
void line_copy(Line *to, Line *from) {
  to->zBuffer = from->zBuffer;
  to->a = from->a;
  to->b = from->b;    
}

void line_print(Line *line, FILE *fp) {
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file!\n");
    exit(1);
  }
    
  fprintf(fp, "Drawing line (%lf, %lf, %lf) to (%lf, %lf, %lf)\n", 
  line->a.val[0],
  line->a.val[1],
  line->a.val[2],
  line->b.val[0],
  line->b.val[1],
  line->b.val[2]);
}

// – draw the line into src using color c and the z-buffer, if appropriate.
void line_draw(Line *line, Image *src, Color color) {
  // check if line points are in Image boundaries
//   if (line->a.val[1] >= src->rows || line->a.val[0] >= src->cols || line->b.val[1] >= src->rows || line->b.val[0] >= src->cols) {
//     printf("Line points are not in image boundary\n");
//     printf("cols, rows: %d, %d\n", src->cols, src->rows);
//     printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
//     printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);
// 	return;
// //     exit(-1);
//   }

  double a_x = line->a.val[0];
  double a_y = line->a.val[1];
  double b_x = line->b.val[0];
  double b_y = line->b.val[1];
  double  x_min = 0.0;
  double  y_min = 0.0;
  double  x_max = src->cols;
  double  y_max = src->rows;
  
  double v_x = b_x - a_x;
  double v_y = b_y - a_y;
  double v_z = line->b.val[2] - line->a.val[2];
  
//   printf("v_x %f\n", v_x);
  
  double p1 = -v_x;
  double p2 = v_x;
  double p3 = -v_y;
  double p4 = v_y;
//  double p5 = -v_z;
//  double p6 = v_z;
  
  double q1 = a_x - x_min;
  double q2 = x_max - a_x;
  double q3 = a_y - y_min;
  double q4 = y_max - a_y;
  
  // loop through all 4 boundaries
  int k;
  double t0 = 0.0; 
  double t_f = 1.0; 
  double t_k, p_k, q_k;
  for (k=0; k<4; k++) {
    
    // ugly, refactor later
    if (k==0) {
      p_k = p1;
      q_k = q1;
    }
    else if (k==1) {
      p_k = p2;
      q_k = q2;
    }
    else if (k==2) {
      p_k = p3;
      q_k = q3;
    }
    else {
      p_k = p4;
      q_k = q4;    
    }       
     
    if (p_k == 0 && q_k <= 0) {
//       printf("Discard %d: pk %.2f qk %.2f\n", k, p_k, q_k);
      return; // discard this line
    }
    else if (p_k == 0)
      continue; // go to next boundary
    
    t_k = q_k / p_k;
    
    if (p_k < 0)
      t0 = t0 > t_k ? t0 : t_k;
    else
      t_f = t_f < t_k ? t_f : t_k;
    
    if (t0 >= t_f)
      return; // discard line
  }
  
  Line new_line; 
  line_set2D(&new_line, a_x + t0*v_x, a_y + t0*v_y-0.1, a_x + t_f*v_x, a_y + t_f*v_y-0.1);
  
  printf("Drawing (%.2f %.2f) (%.2f %.2f)\n", a_x + t0*v_x, a_y + t0*v_y, a_x + t_f*v_x, a_y + t_f*v_y);
  // always start at the bottom and end at the top
  int c1;
  int r1;
  double z1;
  int c2;
  int r2;
  double z2;
  int reversed;
  
//   printf("%d\n",offset);
  
  // reverse start and end 
  // change from x,y coordinates to image coordinates by subtracting from rows offset
  if (new_line.a.val[1] < new_line.b.val[1]) {
    c1 = new_line.b.val[0];
    r1 = new_line.b.val[1];
    z1 = new_line.b.zBuffer;
    c2 = new_line.a.val[0];
    r2 = new_line.a.val[1];
    z2 = new_line.a.zBuffer;
    reversed = 1;
  }
  else {
    c1 = new_line.a.val[0];
    r1 = new_line.a.val[1];
    z1 = new_line.a.zBuffer;
    c2 = new_line.b.val[0];
    r2 = new_line.b.val[1];
    z2 = new_line.b.zBuffer;
    reversed = 0;
  }
//   printf("reversed: %d\n", reversed);
//   printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
//   printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);  
//   printf("(r1, c1): (%d, %d)\n",c1, r1);
//   printf("(r2, c2): (%d, %d)\n",c2, r2);
    
  int dx = c2 - c1;
  int dy = r1 - r2; // not r2 - r1 b/c dy is flipped in image coords
  double d_1byZ;
  double init_z;
  int dx2;
  int dy2;
  float m;
  int e;
  int i;
  
//   printf("dx, dy: %d, %d\n", dx, dy);
  
  
  // vertical line
  if (dx == 0) {
    // vertically color the right side of the line if reversed
    if (!reversed) {
      c1 = c1-1;
      for (i=dy; i--;) {
        image_setColor(src, r1, c1, color);
        r1 = r1 - 1;
      }
    }
    // vertically color the left side of the line if not reversed
    else {
      for (i=dy; i--;) {
        image_setColor(src, r1, c1, color);
        r1 = r1 - 1;
      }
    }
  }
  else {
    // slope is... 
    m = (float)dy/(float)dx;
    
    // precalculate this
    dy2 = dy<<1;
    dx2 = dx<<1;
//     printf("m: %f\n", m);
    
    if (m > 1) { // second octant
//       printf("Second octant\n");
      init_z = src->data[r1*src->cols + c1].z; //// isn't taking into account clipping
      d_1byz = (1/z1 - 1/z2)/dy2; ///// or is it dy2?????
      e = 3*dx - dy2;
      for (i=dy; i--;) {
	    if ( init_z > src->data[r1*src->cols + c1].z ) {
	      src->data[r1*src->cols + c1].z = init_z;
	      image_setColor(src, r1, c1, color);
	    }
	    init_z = init_z + d_1byz;
	    
	    if (e > 0) { // step across
	      c1 = c1 + 1;
	      e = e - dy2;
	    }
	    r1 = r1 - 1; // step up
	    e = e + dx2;
      }
    }
    else if (m > 0) { // not > 1 but positive so first octant 
//       printf("First octant\n");
      init_z = src->data[r1*src->cols + c1].z;
      d_1byz = (1/z1 - 1/z2)/dx2; ///// or is it dx2?????
      e = 3*dy - dx2;
      for (i=dx; i--;) {
        if ( init_z > src->data[r1*src->cols + c1].z ) {
	      src->data[r1*src->cols + c1].z = init_z;
	      image_setColor(src, r1, c1, color);
	    }
	    init_z = init_z + d_1byz;
	    
	    if (e > 0) { // step up
	      r1 = r1 - 1;
	      e = e - dx2;
	    }
	    c1 = c1 + 1; // step across
	    e = e + dy2;
      }
    }
    else if (m < -1) { // third octant
//       printf("Third octant\n");
      init_z = src->data[r2*src->cols + c2].z;
      d_1byz = (1/z1 - 1/z2)/dy2; ///// or is it dx2?????
      e = -3*dx - dy2;
      for (i=dy; i--; ) {
	    if ( init_z > src->data[r2*src->cols + c2].z ) {
	      src->data[r2*src->cols + c2].z = init_z;
	      image_setColor(src, r2, c2, color);
	    }
	    init_z = init_z + d_1byz;
	    
	    if (e > 0) { // step across
	      c2 = c2 + 1;
	      e = e - dy2;
	    }
	    r2 = r2 + 1; // step up
	    e = e - dx2;
      }
    }
    // fourth octant
    else if (m < 0) {
//       printf("Fourth octant\n");
      init_z = src->data[r1*src->cols + c1].z;
      d_1byz = (1/z1 - 1/z2)/dx2; ///// or is it dx2?????
      e = 3*dy + dx2;
      for (i=-dx; i--;) {
	    if ( init_z > src->data[r1*src->cols + c1].z ) {
	      src->data[r1*src->cols + c1].z = init_z;
	      image_setColor(src, r1, c1, color);
	    }
	    init_z = init_z + d_1byz;

	    if (e > 0) { // step across
	      r1 = r1 - 1;
	      e = e + dx2;
	    }
	    c1 = c1 - 1; // step up
	    e = e + dy2;
      }
    }
    else { // horizontal line where dy == 0
//       printf("horizontal\n");
      // horizontally color the top side of the line if dx > 0
      if (dx > 0) {
        for (i=dx; i--; ) {
          image_setColor(src, r1, c1, color);
          c1 = c1 + 1;
        }
      }
      // horizontally color the bottom side of the line if dx < 0
      // also handles point case where dx == 0 && dy == 0, which 
      //  shouldn't color anything
      else {
        r1 = r1 + 1;
        c1 = c1 - 1;
        for (i=-dx; i--; ) {
          image_setColor(src, r1, c1, color);
          c1 = c1 - 1;
        }
      }
      
    } 
  }
} // end of line_draw

// – draw the line into src using color c and the z-buffer, if appropriate.
// test to see if making the color parameter a pointer makes line draw faster
// result: doesn't really make a difference
void line_drawRef(Line *line, Image *src, Color *color) {
  // check if line points are in Image boundaries
  if (line->a.val[1] >= src->rows || line->a.val[0] >= src->cols || line->b.val[1] >= src->rows || line->b.val[0] >= src->cols) {
    printf("Line points are not in image boundary\n");
    printf("cols, rows: %d, %d\n", src->cols, src->rows);
    printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
    printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);
    exit(-1);
  }
  
  // always start at the bottom and end at the top
  int c1;
  int r1;
  int c2;
  int r2;
  int reversed;
  
//   printf("%d\n",offset);
  
  // reverse start and end 
  // change from x,y coordinates to image coordinates by subtracting from rows offset
  if (line->a.val[1] < line->b.val[1]) {
    c1 = line->b.val[0];
    r1 = line->b.val[1];
    c2 = line->a.val[0];
    r2 = line->a.val[1];
    reversed = 1;
  }
  else {
    c1 = line->a.val[0];
    r1 = line->a.val[1];
    c2 = line->b.val[0];
    r2 = line->b.val[1];
    reversed = 0;
  }
//   printf("reversed: %d\n", reversed);
//   printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
//   printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);  
//   printf("(r1, c1): (%d, %d)\n",c1, r1);
//   printf("(r2, c2): (%d, %d)\n",c2, r2);
    
  int dx = c2 - c1;
  int dy = r1 - r2; // not r2 - r1 b/c dy is flipped in image coords
  float m;
  int e;
  int i;
  
//   printf("dx, dy: %d, %d\n", dx, dy);
  
  
  // vertical line
  if (dx == 0) {
    // vertically color the right side of the line if reversed
    if (!reversed) {
      c1 = c1-1;
      for (i=0; i<dy; i++) {
        image_setColor(src, r1, c1, *color);
        r1 = r1 - 1;
      }
    }
    // vertically color the left side of the line if not reversed
    else {
      for (i=0; i<dy; i++) {
        image_setColor(src, r1, c1, *color);
        r1 = r1 - 1;
      }
    }
  }
  else {
    // slope is... 
    m = (float)dy/(float)dx;
    
//     printf("m: %f\n", m);
    
    // second octant
    if (m > 1) {
//       printf("Second octant\n");
      e = 3*dx - (dy<<1);
      for (i=0; i<dy; i++) {
	    image_setColor(src, r1, c1, *color);
	    if (e > 0) { // step across
	      c1 = c1 + 1;
	      e = e - (dy<<1);
	    }
	    r1 = r1 - 1; // step up
	    e = e + (dx<<1);
      }
    }
    // not > 1 but positive so first octant 
    else if (m > 0) {
//       printf("First octant\n");
      e = 3*dy - (dx<<1);
      for (i=0; i<dx; i++) {
	    image_setColor(src, r1, c1, *color);
	    if (e > 0) { // step up
	      r1 = r1 - 1;
	      e = e - (dx<<1);
	    }
	    c1 = c1 + 1; // step across
	    e = e + (dy<<1);
      }
    }
    // third octant
    else if (m < -1) {
//       printf("Third octant\n");
      e = -3*dx - (dy<<1);
      for (i=0; i<dy; i++) {
	    image_setColor(src, r2, c2, *color);
	    if (e > 0) { // step across
	      c2 = c2 + 1;
	      e = e - (dy<<1);
	    }
	    r2 = r2 + 1; // step up
	    e = e - (dx<<1);
      }
    }
    // fourth octant
    else if (m < 0) {
//       printf("Fourth octant\n");
      e = 3*dy + (dx<<1);
      for (i=dx; i<0; i++) {
	    image_setColor(src, r1, c1, *color);
	    if (e > 0) { // step across
	      r1 = r1 - 1;
	      e = e - (-dx<<1);
	    }
	    c1 = c1 - 1; // step up
	    e = e + (dy<<1);
      }
    }
    else { // horizontal line where dy == 0
//       printf("horizontal\n");
      // horizontally color the top side of the line if dx > 0
      if (dx > 0) {
        for (i=0; i<dx; i++) {
          image_setColor(src, r1, c1, *color);
          c1 = c1 + 1;
        }
      }
      // horizontally color the bottom side of the line if dx < 0
      // also handles point case where dx == 0 && dy == 0, which 
      //  shouldn't color anything
      else {
        r1 = r1 + 1;
        c1 = c1 - 1;
        for (i=dx; i<0; i++) {
          image_setColor(src, r1, c1, *color);
          c1 = c1 - 1;
        }
      }
      
    } 
  }
} // end of line_draw

// draw dashed lines
void line_draw_spaced(Line *line, Image *src, Color color, int interval) {
  // check if line points are in Image boundaries
  if (line->a.val[1] >= src->rows || line->a.val[0] >= src->cols || line->b.val[1] >= src->rows || line->b.val[0] >= src->cols) {
    printf("Line points are not in image boundary\n");
    printf("cols, rows: %d, %d\n", src->cols, src->rows);
    printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
    printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);
    exit(-1);
  }
  
  // always start at the bottom and end at the top
  int c1;
  int r1;
  int c2;
  int r2;
  int counter = 0;
  int reversed;
  
//   printf("%d\n",offset);
  
  // reverse start and end 
  // change from x,y coordinates to image coordinates by subtracting from rows offset
  if (line->a.val[1] < line->b.val[1]) {
    c1 = line->b.val[0];
    r1 = line->b.val[1];
    c2 = line->a.val[0];
    r2 = line->a.val[1];
    reversed = 1;
  }
  else {
    c1 = line->a.val[0];
    r1 = line->a.val[1];
    c2 = line->b.val[0];
    r2 = line->b.val[1];
    reversed = 0;
  }
//   printf("reversed: %d\n", reversed);
//   printf("(x1, y1): (%lf, %lf)\n", line->a.val[0], line->a.val[1]);
//   printf("(x2, y2): (%lf, %lf)\n", line->b.val[0], line->b.val[1]);  
//   printf("(r1, c1): (%d, %d)\n",c1, r1);
//   printf("(r2, c2): (%d, %d)\n",c2, r2);
    
  int dx = c2 - c1;
  int dy = r1 - r2; // not r2 - r1 b/c dy is flipped in image coords
  float m;
  int e;
  int i;
  
//   printf("dx, dy: %d, %d\n", dx, dy);
  
  
  // vertical line
  if (dx == 0) {
    // vertically color the right side of the line if reversed
    if (!reversed) {
      c1 = c1-1;
      for (i=0; i<dy; i++) {
        if (!(counter % interval)) {
          image_setColor(src, r1, c1, color);
        }
        r1 = r1 - 1;
        counter++;
      }
    }
    // vertically color the left side of the line if not reversed
    else {
      for (i=0; i<dy; i++) {
        if (!(counter % interval)) {
          image_setColor(src, r1, c1, color);
        }
        r1 = r1 - 1;
        counter++;
      }
    }
  }
  else {
    // slope is... 
    m = (float)dy/(float)dx;
    
//     printf("m: %f\n", m);
    
    // second octant
    if (m > 1) {
//       printf("Second octant\n");
      e = 3*dx - (dy<<1);
      for (i=0; i<dy; i++) {
	    if (!(counter % interval)) {
          image_setColor(src, r1, c1, color);
        }
        counter++;
	    if (e > 0) { // step across
	      c1 = c1 + 1;
	      e = e - (dy<<1);
	    }
	    r1 = r1 - 1; // step up
	    e = e + (dx<<1);
      }
    }
    // not > 1 but positive so first octant 
    else if (m > 0) {
//       printf("First octant\n");
      e = 3*dy - (dx<<1);
      for (i=0; i<dx; i++) {
	    if (!(counter % interval)) {
          image_setColor(src, r1, c1, color);
        }
        counter++;
	    if (e > 0) { // step up
	      r1 = r1 - 1;
	      e = e - (dx<<1);
	    }
	    c1 = c1 + 1; // step across
	    e = e + (dy<<1);
      }
    }
    // third octant
    else if (m < -1) {
//       printf("Third octant\n");
      e = -3*dx - (dy<<1);
      for (i=0; i<dy; i++) {
	    if (!(counter % interval)) {
          image_setColor(src, r2, c2, color);
        }
        counter++;
	    if (e > 0) { // step across
	      c2 = c2 + 1;
	      e = e - (dy<<1);
	    }
	    r2 = r2 + 1; // step up
	    e = e - (dx<<1);
      }
    }
    // fourth octant
    else if (m < 0) {
//       printf("Fourth octant\n");
      e = 3*dy + (dx<<1);
      for (i=dx; i<0; i++) {
	    if (!(counter % interval)) {
          image_setColor(src, r1, c1, color);
        }
        counter++;
	    if (e > 0) { // step across
	      r1 = r1 - 1;
	      e = e - (-dx<<1);
	    }
	    c1 = c1 - 1; // step up
	    e = e + (dy<<1);
      }
    }
    else { // horizontal line where dy == 0
//       printf("horizontal\n");
      // horizontally color the top side of the line if dx > 0
      if (dx > 0) {
        for (i=0; i<dx; i++) {
          if (!(counter % interval)) {
            image_setColor(src, r1, c1, color);
          }
          counter++;
          c1 = c1 + 1;
        }
      }
      // horizontally color the bottom side of the line if dx < 0
      // also handles point case where dx == 0 && dy == 0, which 
      //  shouldn't color anything
      else {
        r1 = r1 + 1;
        c1 = c1 - 1;
        for (i=dx; i<0; i++) {
          if (!(counter % interval)) {
            image_setColor(src, r1, c1, color);
          }
          counter++;
          c1 = c1 - 1;
        }
      }
      
    } 
  }
} // end of line_draw


// returns an allocated Polyline pointer initialized 
// so that numVertex is 0 and vertex is NULL.
Polyline *polyline_create() {
  Polyline *pline = malloc(sizeof(Polyline));
  
  if (!pline) {
    printf("Ran out of memory while mallocing Polyline pointer in polyline_create!\n");
    exit(-1);
  }
  
  pline->zBuffer = 1.0;
  pline->numVertex = 0;
  pline->vertex = NULL;
  
  return pline;
}

// returns an allocated Polyline pointer with the vertex list 
// initialized to the points in vlist.
Polyline *polyline_createp( int numV, Point *vlist ) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polyline_createp!\n");
    exit(-1);
  }
  
  Polyline *pline = malloc(sizeof(Polyline));
  
  if (!pline) {
    printf("Ran out of memory while mallocing Polyline pointer in polyline_createp!\n");
    exit(-1);
  }
  
  pline->vertex = malloc(sizeof(Point) * numV);
  
  if (!pline->vertex) {
    printf("Ran out of memory while mallocing vertex pointer in polyline_set!\n");
    free(pline);
    exit(-1);
  }
  int i;
  
  for (i=0; i<numV; i++) {
    pline->vertex[i] = vlist[i];
  }
  
  pline->zBuffer = 1.0;
  pline->numVertex = numV;
  
  return pline;
}

// frees the internal data and the Polyline pointer
void polyline_free(Polyline *p) {
  if (p->vertex) {
    free(p->vertex);
    p->vertex = NULL;
  }
  if (p) {
    free(p);
    p = NULL;
  }
}


// initializes the pre-existing Polyline to an empty Polyline
void polyline_init( Polyline *pline ) {
  pline->numVertex = 0;
  pline->zBuffer = 1.0;
  pline->vertex = NULL;
}

// initializes the vertex list to the points in vlist. 
// De-allocates/allocates the vertex list for p, as necessary.
void polyline_set( Polyline *pline, int numV, Point *vlist ) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polyline_set!\n");
    exit(-1);
  }
  
  pline->vertex = malloc(sizeof(Point) * numV);
  
  if (!pline->vertex) {
    printf("Ran out of memory while mallocing vertex pointer in polyline_set!\n");
    exit(-1);
  }
  int i;
  
  pline->zBuffer = 1.0;
  pline->numVertex = numV;
  for (i=0; i<numV; i++) {
    pline->vertex[i] = vlist[i];
  }
  
}

// frees the internal data for a Polyline, if necessary, 
// and sets numVertex to 0 and vertex to NULL.
void polyline_clear(Polyline *p) {
  if (p->vertex) {
    free(p->vertex);
  }
  
  p->numVertex = 0;
  p->zBuffer = 1.0;
  p->vertex = NULL;
}

// sets the z-buffer flag to the given value
void polyline_zBuffer(Polyline *p, int flag) {
  p->zBuffer = flag;
}

// De-allocates/allocates space as necessary in the destination 
// Polyline data structure and copies the vertex data from the 
// source polyline (from) to the destination (to).
void polyline_copy(Polyline *to, Polyline *from) {
  int i;

  if (!to->vertex) {
    to->vertex = malloc(sizeof(Point) * from->numVertex);
  }
  else {
    free(to->vertex);
    to->vertex = malloc(sizeof(Point) * from->numVertex);
  }
  
  to->numVertex = from->numVertex;
  to->zBuffer = from->zBuffer;
  
  
  for (i=0; i<from->numVertex; i++) {
    to->vertex[i] = from->vertex[i];
  }
  
// free source at a higher level
//   free(from->vertex);
//   free(from);
}

// prints Polyline data to the stream designated by the FILE pointer.
void polyline_print(Polyline *p, FILE *fp) {
  char *filename = "pline_content.txt";
  int i;
  
  fp = fopen(filename, "w");
  
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file %s!\n", filename);
    exit(1);
  }


  fprintf(fp, "zBuffer: %d\n", p->zBuffer);
  fprintf(fp, "numVertex: %d\n", p->numVertex);
  for (i=0; i<p->numVertex; i++) {
    fprintf(fp, "(x, y, z, h): (%lf, %lf, %lf, %lf)\n", 
      p->vertex[i].val[0],
      p->vertex[i].val[1],
      p->vertex[i].val[2],
      p->vertex[i].val[3]);
  }
}

// normalize the x and y values of each vertex by the homogeneous coordinate.
void polyline_normalize( Polyline *p ) {
  int i;
  
  for (i=0; i<p->numVertex; i++) {
    p->vertex[i].val[0] /= p->vertex[i].val[3];
    p->vertex[i].val[1] /= p->vertex[i].val[3];
  }
}

// draw the polyline using color c and the z-buffer, if appropriate.
void polyline_draw(Polyline *p, Image *src, Color c) {
  int i;
  int numVertex = p->numVertex;
  Line line;
  
  for (i=0; i<numVertex-1; i++) {
    line_set(&line, p->vertex[i], p->vertex[i+1]);
    line_draw(&line, src, c);
  }
}
