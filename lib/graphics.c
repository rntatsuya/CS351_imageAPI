/*
 * Tatsuya Yokota
 * graphics.c
 * 
 */

#include "graphics.h"

// check row/col to row/col color equality
int checkColorEq_rc2rc(Image *src, int r1, int c1, int r2, int c2) {
  if (r1 < 0 || r1 >= src->rows || c1 < 0 || c1 >= src->cols || r2 < 0 || r2 >= src->rows || c2 < 0 || c2 >= src->cols) {
    printf("Row or Col out of bounds at checkColorEq_rc2rc\n");
    return 0;
  }

  return src->data[r1*src->cols + c1].rgb[0] == src->data[r2*src->cols + c2].rgb[0] \
  && src->data[r1*src->cols + c1].rgb[1] == src->data[r2*src->cols + c2].rgb[1] \
  && src->data[r1*src->cols + c1].rgb[2] == src->data[r2*src->cols + c2].rgb[2];
}

// check row/col to color struct color equality
int checkColorEq_rc2color(Image *src, int r, int c, Color color) {
  if (r < 0 || r >= src->rows || c < 0 || c >= src->cols) {
    printf("Row or Col out of bounds at checkColorEq_rc2color\n");
    return 0;
  }
  
  return src->data[r*src->cols + c].rgb[0] == color.c[0]\
  && src->data[r*src->cols + c].rgb[1] ==  color.c[1]\
  && src->data[r*src->cols + c].rgb[2] == color.c[2];
}

// check point to point color equality
// int checkColorEq_rc2rc(Image *src, Point a, Point b) {
//   return src->data[r1*src->cols + c1].rgb[0] == src->data[r2*src->cols + c2].rgb[0] \
//   && src->data[r1*src->cols + c1].rgb[1] == src->data[r2*src->cols + c2].rgb[1] \
//   && src->data[r1*src->cols + c1].rgb[2] == src->data[r2*src->cols + c2].rgb[2];
// }

// given a seed pixel, a boundary color, and fill color, 
// fills in all pixels within the specified boundary color
void floodFill(Image *src, Point seed, Color b_color, Color f_color) {
  int cols = src->cols;
  Point curPoint;
  int c;
  int r;
  int left_c;
  int right_c;
  Point stk[src->rows];
  int stk_height = 0;
  int stop = 0;
  int top_done = 0;
  int bottom_done = 0;
  
  // push seed onto stack
  stk[stk_height++] = seed;
  
  // loop until stk_height == 0
  while (stk_height != 0) {
    // pop point from stack
    curPoint = stk[--stk_height];
    c = curPoint.val[0];
    r = curPoint.val[1];
    // go left and then right, while checking pixel above and below
    // if not b_color and f_color, push to stack
    // if we reach boundary on right, search left of curPoint 
    // if we reach boundary on left, pop pixel from stack
      
    // go left first (also includes current point)
    left_c = c;
    while (!stop && left_c >= 0) {
      
      // check equality between curPoint color and b_color
      if (checkColorEq_rc2color(src, r, left_c, b_color)) {
        stop = 1;
        break;
      }
      else if (!checkColorEq_rc2color(src, r, left_c, f_color)) {
        image_setColor(src, r, left_c, f_color);
      }
      
      // check pixel above if we haven't found a non-boundary for that row yet
      if (!top_done) {
        // if non-boundary and non-fill color, push to stack      
        if (!checkColorEq_rc2color(src, r-1, left_c, b_color) && !checkColorEq_rc2color(src, r-1, left_c, f_color)) {
          stk[stk_height++] = point_create2D(left_c, r-1);
          top_done = 1;
        }
      }
      
      // check pixel below if we haven't found a non-boundary for that row yet
      if (!bottom_done) {
        // if non-boundary and non-fill color, push to stack
        if (!checkColorEq_rc2color(src, r+1, left_c, b_color) && checkColorEq_rc2color(src, r+1, left_c, f_color)) {
          stk[stk_height++] = point_create2D(left_c, r+1);
          bottom_done = 1;
        }
      }
      
      // keep going left
      left_c -= 1;
    }
    
    
    // go right
    stop = 0;
    top_done = 0;
    bottom_done = 0;
    right_c = c+1;
    while (!stop && right_c < cols) {
      
      // check equality between curPoint color and b_color
      if (checkColorEq_rc2color(src, r, right_c, b_color)) {
        stop = 1;
        break;
      }
      else if (!checkColorEq_rc2color(src, r, right_c, f_color)) {
        image_setColor(src, r, right_c, f_color);
      }
      
      // check pixel above if we haven't found a non-boundary for that row yet
      if (!top_done) {
        // if non-boundary and non-fill color, push to stack  
        if (!checkColorEq_rc2color(src, r-1, right_c, b_color) && !checkColorEq_rc2color(src, r-1, right_c, f_color)) {
          stk[stk_height++] = point_create2D(right_c, r-1);
          top_done = 1;
        }    
      }
      
      // check pixel below if we haven't found a non-boundary for that row yet
      if (!bottom_done) {
        // if non-boundary and non-fill color, push to stack  
        if (!checkColorEq_rc2color(src, r+1, right_c, b_color) && !checkColorEq_rc2color(src, r+1, right_c, f_color)) {
          stk[stk_height++] = point_create2D(right_c, r+1);
          top_done = 1;
        }    
      }

      // keep going right
      right_c += 1;
    }
    stop = 0;
    top_done = 0;
    bottom_done = 0;
  }
}
// 
// // given a seed pixel, a boundary color, and fill color, 
// // fills in all pixels within the specified boundary color
// void floodFillGradient(Image *src, Point seed, Color b_color, int radius, Color f_color1, Color f_color2) {
//   int cols = src->cols;
//   Point curPoint;
//   int c;
//   int r;
//   int left_c;
//   int right_c;
//   int seed_c = seed.val[0];
//   int seed_r = seed.val[1];  
//   Point stk[src->rows];
//   int stk_height = 0;
//   int stop = 0;
//   int top_done = 0;
//   int bottom_done = 0;
//   
//   // push seed onto stack
//   stk[stk_height++] = seed;
//   
//   // loop until stk_height == 0
//   while (stk_height != 0) {
//     // pop point from stack
//     curPoint = stk[--stk_height];
//     c = curPoint.val[0];
//     r = curPoint.val[1];
//     // go left and then right, while checking pixel above and below
//     // if not b_color and f_color, push to stack
//     // if we reach boundary on right, search left of curPoint 
//     // if we reach boundary on left, pop pixel from stack
//     
//     printf("here %d\n", stk_height);
//     
//     // go left first (also includes current point)
//     left_c = c;
//     while (!stop && left_c >= 0) {
//       
//       // check equality between curPoint color and b_color
//       if (checkColorEq_rc2color(src, r, left_c, b_color)) {
//         stop = 1;
//         break;
//       }
//       else {
//         image_setColorGradient(src, seed_r, seed_c, r, left_c, radius, f_color1, f_color2);
//       }
//       
//       // check pixel above if we haven't found a non-boundary for that row yet
//       if (!top_done) {
//         // if non-boundary and non-fill color, push to stack      
//         if (!checkColorEq_rc2color(src, r-1, left_c, b_color)) {
//           stk[stk_height++] = point_create2D(left_c, r-1);
//           top_done = 1;
//         }
//       }
//       
//       // check pixel below if we haven't found a non-boundary for that row yet
//       if (!bottom_done) {
//         // if non-boundary and non-fill color, push to stack
//         if (!checkColorEq_rc2color(src, r+1, left_c, b_color)) {
//           stk[stk_height++] = point_create2D(left_c, r+1);
//           bottom_done = 1;
//         }
//       }
//       
//       // keep going left
//       left_c -= 1;
//     }
//     
//     
//     // go right
//     stop = 0;
//     top_done = 0;
//     bottom_done = 0;
//     right_c = c+1;
//     while (!stop && right_c < cols) {
//       
//       // check equality between curPoint color and b_color
//       if (checkColorEq_rc2color(src, r, right_c, b_color)) {
//         stop = 1;
//         break;
//       }
//       else {
//         image_setColorGradient(src, seed_r, seed_c, r, right_c, radius, f_color1, f_color2);
//       }
//       
//       // check pixel above if we haven't found a non-boundary for that row yet
//       if (!top_done) {
//         // if non-boundary and non-fill color, push to stack  
//         if (!checkColorEq_rc2color(src, r-1, right_c, b_color)) {
//           stk[stk_height++] = point_create2D(right_c, r-1);
//           top_done = 1;
//         }    
//       }
//       
//       // check pixel below if we haven't found a non-boundary for that row yet
//       if (!bottom_done) {
//         // if non-boundary and non-fill color, push to stack  
//         if (!checkColorEq_rc2color(src, r+1, right_c, b_color)) {
//           stk[stk_height++] = point_create2D(right_c, r+1);
//           top_done = 1;
//         }    
//       }
// 
//       // keep going right
//       right_c += 1;
//     }
//     stop = 0;
//     top_done = 0;
//     bottom_done = 0;
//   }
// }

