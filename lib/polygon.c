#include <stdlib.h>
#include <stdio.h>
#include "line.h"
#include "polygon.h"
#include "drawstate.h"
#include "lighting.h"

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
  
  p->vertex = malloc(sizeof(Point) * numV);
  
  if (!p->vertex) {
    printf("Ran out of memory while mallocing vertex pointer in polygon_set!\n");
    free(p);
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
    free(p);
    exit(-1);
  }
//   printf("in polygon_set, setting %d vertices\n", numV);
  int i;
  for (i=0; i<numV; i++) {
    p->vertex[i] = vlist[i];
//     printf("%d\n", i);
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
    free(p);
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
//   
//   // check if there's already memory allocated for the vertex field
//   if (!to->vertex) {
//     printf("here\n");
//     to->vertex = malloc(sizeof(Point) * nVertex);
//   }
//   else {
//     free(to->vertex);
//     to->vertex = malloc(sizeof(Point) * nVertex);
//   }
// 
//   // check if there's already memory allocated for the color field  
//   if (!to->color) {
// //     printf("here\n");
//     to->color = malloc(sizeof(Color) * nVertex);
//   }
//   else {
// //   	printf("ho\n");
//     free(to->color);
//     to->color = malloc(sizeof(Color) * nVertex);
//   }
  
//   printf("%d\n",nVertex);
//   printf("%.2f\n", to->vertex[0]);
  // need to make sure enough memory is allocated to vertex list field
  to->vertex = malloc(sizeof(Point) * nVertex);
  
//   printf("in polygon_copy, copying polygon\n");
  // copy content from source
  for (i=0; i<nVertex; i++) {
    to->vertex[i].val[0] = from->vertex[i].val[0];
    to->vertex[i].val[1] = from->vertex[i].val[1];
    to->vertex[i].val[2] = from->vertex[i].val[2];
    to->vertex[i].val[3] = from->vertex[i].val[3];
//     to->color[i] = from->color[i];     
  }
  
//   printf("in polygon_copy, finished copying polygon\n");
  to->nVertex = nVertex;
  to->zBuffer = from->zBuffer;
  
  // free memory at a higher level
//   free(from->vertex);
//   free(from);
}


void polygon_print(Polygon *p, FILE *fp) {
  int i;
  
  if (fp == NULL) {
    fprintf(stderr, "Can't open output file!\n");
    exit(1);
  }


//   fprintf(fp, "zBuffer: %d\n", p->zBuffer);
//   fprintf(fp, "numVertex: %d\n", p->nVertex);
//   fprintf(fp, "oneSided: %d\n", p->oneSided);
  for (i=0; i<p->nVertex; i++) {
    fprintf(fp, "(%lf, %lf, %lf)\n", 
      p->vertex[i].val[0],
      p->vertex[i].val[1],
      p->vertex[i].val[2]);
//       p->vertex[i].val[3]);
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
  printf("connecting here\n");
  line_set(&line, p->vertex[0], p->vertex[i]);
  line_draw(&line, src, c);
  printf("done\n");  
}

void polygon_drawFrame( Polygon *p, Image *src, Color c ) {
  int i;
  int numVertex = p->nVertex;
  Line line;
  
//   printf("numVertex: %d\n", numVertex);
  // connect all points except for first and last
  for (i=0; i<numVertex-1; i++) {
//     printf("%d, %d\n", i, i+1);
    line_set(&line, p->vertex[i], p->vertex[i+1]);
//     printf("Drawing from and to:\n");
//     point_print(&p->vertex[i], stdout);
//     point_print(&p->vertex[i+1], stdout);
    line_draw(&line, src, c);
  }
  
  
  // connect first and last points
  line_set(&line, p->vertex[0], p->vertex[i]);
//   printf("Drawing from and to:\n");
//   point_print(&p->vertex[0], stdout);
//   point_print(&p->vertex[i], stdout);
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


// uses barycentric coordinates to determine which pixels to fill given a polygon 
// with only 3 points
void polygon_drawFillBGradient(Polygon *p, Image *src, Color c1, Color c2, Color c3) {    
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
//       image_setColor(src, (int)cur_y, (int)cur_x, c);
      image_setc(src, (int)cur_y, (int)cur_x, 0, c1.c[0]*alpha + c2.c[0]*beta + c3.c[0]*gamma);
      image_setc(src, (int)cur_y, (int)cur_x, 1, c1.c[1]*alpha + c2.c[1]*beta + c3.c[1]*gamma);
      image_setc(src, (int)cur_y, (int)cur_x, 2, c1.c[2]*alpha + c2.c[2]*beta + c3.c[2]*gamma);
    }
  }
}

void polygon_drawShade(Polygon *p, Image *src, DrawState *ds, Lighting *light) {
  printf("in drawshade %d\n", ds->shade);
  color_print(&ds->color, stdout);
  switch (ds->shade) {
    case ShadeFrame: 
      {
        printf("drawing shade frame!\n");
        polygon_draw(p, src, ds->color);
        break;
      }
    case ShadeConstant: 
      {
        printf("drawing shade constant!\n");
        polygon_drawState( p, src, ds );
        break;
      }
    case ShadeDepth: 
      {
        printf("drawing shade depth!\n");
        polygon_drawState( p, src, ds );
        break;
      }
    case ShadeFlat: 
      {
        printf("drawing shade flat!\n");
        break;
      }
    case ShadeGouraud:
      {
        printf("drawing shade gouraud!\n");
        break;
      }
    case ShadePhong: 
      {
        printf("drawing shade phong!\n");
        break;
      }
    default:
      {
        printf("default\n");
        break;
      }
  }

}

// initializes the normal array to the vectors in nlist.
void polygon_setNormals(Polygon *p, int numV, Vector *nlist) {
  // set polygon normal to vectors in nlist (maccloc)
  p->normal = malloc(numV*sizeof(Vector));
  for ( int i = 0; i < numV; i++ ) 
    vector_copy( &p->normal[i], &nlist[i] );
}
