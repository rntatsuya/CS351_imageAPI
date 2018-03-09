#include <stdlib.h>
#include <stdio.h>
#include "line.h"
#include "polygon.h"

Polygon *polygon_create() {
  Polygon *p = malloc(sizeof(Polygon));
  
  if (!p) {
    printf("Ran out of memory while mallocing Polygon pointer in polygon_create!\n");
    exit(-1);
  }
  
  p->zBuffer = 1;
  p->nVertex = 0;
  p->vertex = NULL;
  p->color = NULL;
//   p->normal = NULL;
  p->oneSided = 1;
  
  return p;
}

Polygon *polygon_createp(int numV, Point *vlist) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polygon_createp!\n");
    exit(-1);
  }
  
  Polygon *p = malloc(sizeof(Polygon));
  
  if (!p) {
    printf("Ran out of memory while mallocing Polygon pointer in polygon_createp!\n");
    exit(-1);
  }
  
  p->zBuffer = 1;
  p->nVertex = numV;
  p->vertex = vlist;
  p->color = NULL;
//   p->normal = NULL;
  p->oneSided = 1;
  
  return p;
}

void polygon_free(Polygon *p) {
  if (p->vertex) {
    free(p->vertex);
    p->vertex = NULL;
  }
  if (p->color) {
    free(p->color);
    p->color = NULL;
  }
//   if (p->normal) {
//     free(p->normal);
//     p->normal = NULL;
//   }
  if (p) {
    free(p);
    p = NULL;
  }
}


void polygon_init(Polygon *p) {
  p->zBuffer = 1;
  p->nVertex = 0;
  p->vertex = NULL;
  p->color = NULL;
//   p->normal = NULL;
  p->oneSided = 1;
}

void polygon_set(Polygon *p, int numV, Point *vlist) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polygon_set!\n");
    exit(-1);
  }
  
  p->vertex = malloc(sizeof(Point) * numV);
  
  if (!p->vertex) {
    printf("Ran out of memory while mallocing vertex pointer in polygon_set!\n");
    exit(-1);
  }
  
  int i;
  for (i=0; i<numV; i++) {
    p->vertex[i] = vlist[i];
  }
  
  p->zBuffer = 1;
  p->nVertex = numV;  
  p->color = NULL;
//   p->normal = NULL;
  p->oneSided = 1;
}



void polygon_clear(Polygon *p) {
  if (p->vertex) {
    free(p->vertex);
    p->vertex = NULL;
  }
  if (p->color) {
    free(p->color);
    p->color = NULL;
  }
//   if (p->normal) {
//     free(p->normal);
//     p->normal = NULL;
//   }
  
  p->zBuffer = 1;
  p->nVertex = 0;
  p->oneSided = 1;
}


void polygon_setSided(Polygon *p, int oneSided) {
  p->oneSided = oneSided;
}

void polygon_setColors(Polygon *p, int numV, Color *clist) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polygon_setColors!\n");
    exit(-1);    
  }
  
  p->color = malloc(sizeof(Color) * numV);
  
  if (!p->color) {
    printf("Ran out of memory while mallocing colors pointer in polygon_setColors!\n");
    exit(-1);
  }
  
  int i;
  for (i=0; i<numV; i++) {
    p->color[i] = clist[i];
  }
}
// 
// void polygon_setNormals(Polygon *p, int numV, Vector *nlist) {
//   if (numV < 0) {
//     printf("numVertex cannot be negative in polygon_setNormals!\n");
//     exit(-1);    
//   }
//   
//   p->normal = malloc(sizeof(Vector) * numV);
//   
//   if (!p->normal) {
//     printf("Ran out of memory while mallocing normals pointer in polygon_setNormals!\n");
//     exit(-1);
//   }
//   
//   int i;
//   for (i=0; i<numV; i++) {
//     p->normal[i] = nlist[i];
//   }
// }

// void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, Vector *nlist, int zBuffer, int oneSided) {
//   if (numV < 0) {
//     printf("numVertex cannot be negative in polygon_setNormals!\n");
//     exit(-1);    
//   }
//   
//   p->vertex = malloc(sizeof(Point) * numV);
//   p->normal = malloc(sizeof(Vector) * numV);
//   p->colors = malloc(sizeof(Color) * numV);
//   
//   if (!p->vertex || !p->normal || !p->colors) {
//     printf("Ran out of memory while mallocing in polygon_setAll!\n");
//     exit(-1);
//   }
//   
//   int i;
//   for (i=0; i<numV; i++) {
//     p->vertex[i] = vlist[i];
//     p->normal[i] = nlist[i];
//     p->colors[i] = clist[i];
//   }
//   
//   p->zBuffer = zBuffer;
//   p->nVertex = numV;
//   p->oneSided = oneSided;
// }

void polygon_zBuffer(Polygon *p, int flag) {
  p->zBuffer = flag;
}

void polygon_copy(Polygon *to, Polygon *from) {
  int i;
  int nVertex = from->nVertex;
  
  // check if there's already memory allocated for the vertex field
  if (!to->vertex) {
    to->vertex = malloc(sizeof(Point) * nVertex);
  }
  else {
    free(to->vertex);
    to->vertex = malloc(sizeof(Point) * nVertex);
  }

  // check if there's already memory allocated for the color field  
  if (!to->color) {
    to->color = malloc(sizeof(Color) * nVertex);
  }
  else {
    free(to->color);
    to->color = malloc(sizeof(Color) * nVertex);
  }
  
  // copy content from source
  for (i=0; i<nVertex; i++) {
    to->vertex[i] = from->vertex[i];
    to->color[i] = from->color[i];
  }
  
  to->nVertex = nVertex;
  to->zBuffer = from->zBuffer;
  
  // free memory at a higher level
//   free(from->vertex);
//   free(from);
}


void polygon_print(Polygon *p, FILE *fp) {
  char *filename = "pline_content.txt";
  int i;
  
  fp = fopen(filename, "w");
  
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file %s!\n", filename);
    exit(1);
  }


  fprintf(fp, "zBuffer: %d\n", p->zBuffer);
  fprintf(fp, "numVertex: %d\n", p->nVertex);
  fprintf(fp, "oneSided: %d\n", p->oneSided);
  for (i=0; i<p->nVertex; i++) {
    fprintf(fp, "(x, y, z, h): (%lf, %lf, %lf, %lf)\n", 
      p->vertex[i].val[0],
      p->vertex[i].val[1],
      p->vertex[i].val[2],
      p->vertex[i].val[3]);
  }
}

void polygon_normalize( Polygon *p ) {
  int i;
  
  for (i=0; i<p->nVertex; i++) {
    p->vertex[i].val[0] /= p->vertex[i].val[3];
    p->vertex[i].val[1] /= p->vertex[i].val[3];
  }
}


void polygon_draw(Polygon *p, Image *src, Color c) {
  int i;
  int numVertex = p->nVertex;
  Line line;
  
  // connect all points except for first and last
  for (i=0; i<numVertex-1; i++) {
    printf("%d, %d\n", i, i+1);
    line_set(&line, p->vertex[i], p->vertex[i+1]);
    line_draw(&line, src, c);
  }
  
  // connect first and last points
  line_set(&line, p->vertex[0], p->vertex[i+1]);
  line_draw(&line, src, c);
  
}

// uses barycentric coordinates to determine which pixels to fill given a polygon 
// with only 3 points
void polygon_drawFillB(Polygon *p, Image *src, Color c) {    
  // if polygon doesn't have 3 vertices, exit
  if (p->nVertex != 3) {
    printf("Number of vertices of Polygon have to be three in polygon_drawFillB\nGot %d\n", p->nVertex);
    exit(-1);
  }
  
  // box_x is leftmost col, box_y is topmost row
  // box_dx is col dif between furthest two points in terms of cols 
  // box_dy is row dif between furthest two points in terms of rows 
  float box_x, box_y;
  int box_dx, box_dy;
  float alpha, beta, gamma;
  float x_a = p->vertex[0].val[0]; 
  float y_a = p->vertex[0].val[1];
  float x_b = p->vertex[1].val[0];
  float y_b = p->vertex[1].val[1];
  float x_c = p->vertex[2].val[0];
  float y_c = p->vertex[2].val[1];
  int i,j;
  
/////// CAN PROBABLY UNROLL FOR LOOP HERE TO INCREASE SPEED///////////
  // find info of bounding box of the triangle
  // i.e. keep the highest and lowest row
  //   and the most left and most right column 
  // to get the top left corner and dx, dy of the box
  box_x = x_a;
  box_y = y_a;
  box_dx = 0;
  box_dy = 0;  
  for (i=1; i<3; i++) {
    // compare x
    if (p->vertex[i].val[0] < box_x) {
      box_x = p->vertex[i].val[0];
    }
    // compare y
    if (p->vertex[i].val[1] < box_y) {
      box_y = p->vertex[i].val[1];
    }
  }
  // keep track of greatest dx, dy
  for (i=0; i<3; i++) {
    if (p->vertex[i].val[0] - box_x > box_dx) {
      box_dx = round(p->vertex[i].val[0] - box_x);
    }
    
    if (p->vertex[i].val[1] - box_y > box_dy) {
      box_dy = round(p->vertex[i].val[1] - box_y);
    }
  }
  
  printf("box_x: %f\nbox_y: %f\nbox_dx: %d\nbox_dy: %d\n",box_x, box_y, box_dx, box_dy);
  
  float x_v0;
  float x_v1;
  float x_v2;
  float y_v0;
  float y_v1;
  float y_v2;
  float d00, d01, d11, d20, d21, denom;
  
  float cur_x = box_x + 0.5;
  float cur_y = box_y + 0.5;
  
  // loop through all points in the bounding box of the triangle
  for (i=0; i<box_dx; i++) {
    cur_x += 1;
    cur_y = box_y + 0.5;
    for (j=0; j<box_dy; j++) {
      cur_y += 1;
      
//       printf("box_x, box_y: %d, %d\n", cur_x, cur_y);
      
      x_v0 = x_b - x_a;
      y_v0 = y_b - y_a;
      x_v1 = x_c - x_a;
      y_v1 = y_c - y_a;
      x_v2 = cur_x - x_a;
      y_v2 = cur_y - y_a;
      
      d00 = x_v0*x_v0 + y_v0*y_v0;
      d01 = x_v0*x_v1 + y_v0*y_v1;
      d11 = x_v1*x_v1 + y_v1*y_v1;
      d20 = x_v2*x_v0 + y_v2*y_v0;
      d21 = x_v2*x_v1 + y_v2*y_v1;
      denom = d00 * d11 - d01 * d01;
      
      beta = (d11 * d20 - d01 * d21) / denom;
      gamma = (d00 * d21 - d01 * d20) / denom;
      
      alpha = 1 - beta - gamma;
      
//       printf("alpha: %f\nbeta: %f\ngamma: %f\n", alpha, beta, gamma);
      // checking for ors is faster than checking for a lot of ands
      if (alpha < 0 || beta < 0 || gamma < 0) {
//         printf("x, y: %f, %f\n", cur_x, cur_y);
        continue;
      }
      image_setColor(src, (int)cur_y, (int)cur_x, c);
    }
  }
}

