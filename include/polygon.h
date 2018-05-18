#ifndef POLYGON_H

#define POLYGON_H


#include <stdio.h>
#include "line.h"
#include "vector.h"
#include "image.h"
#include "color.h"
#include "drawstate.h"
#include "lighting.h"

typedef struct {
  int oneSided; 
  int nVertex;
  Point *vertex;  // vertex information
  Color *color;  //  color information for each vertex
  Vector *normal; //  surface normal information for each vertex.
  double zBuffer;
} Polygon;

// returns an allocated Polygon pointer initialized 
// so that numVertex is 0 and vertex is NULL.
Polygon *polygon_create(void);

// returns an allocated Polygon pointer with the 
// vertex list initialized to a copy of the points in vlist.
Polygon *polygon_createp(int numV, Point *vlist);

// frees the internal data for a Polygon and the Polygon pointer.
void polygon_free(Polygon *p);

// initializes the existing Polygon to an empty Polygon.
void polygon_init(Polygon *p);

// initializes the vertex array to the points in vlist.
void polygon_set(Polygon *p, int numV, Point *vlist);

// frees the internal data and resets the fields.
void polygon_clear(Polygon *p);

// sets the oneSided field to the value.
void polygon_setSided(Polygon *p, int oneSided);

// initializes the color array to the colors in clist
void polygon_setColors(Polygon *p, int numV, Color *clist);

// initializes the normal array to the vectors in nlist.
// void polygon_setNormals(Polygon *p, int numV, Vector *nlist);

// initializes the vertex list to the points in vlist, the colors to the colors in clist, 
// the normals to the vectors in nlist, and the zBuffer and oneSided flags 
// to their respectively values.
void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, Vector *nlist, double zBuffer, int oneSided);

// sets the z-buffer flag to the given value.
void polygon_zBuffer(Polygon *p, double flag);

// De-allocates/allocates space and copies the vertex and color data from one polygon to the other.
void polygon_copy(Polygon *to, Polygon *from);

// prints polygon data to the stream designated by the FILE pointer.
void polygon_print(Polygon *p, FILE *fp);

// normalize the x and y values of each vertex by the homogeneous coord.
void polygon_normalize( Polygon *p );

// draw the outline of the polygon using color c.
void polygon_draw(Polygon *p, Image *src, Color c);

void polygon_drawFrame( Polygon *p, Image *src, Color c );

void polygon_drawState(Polygon *p, Image *src, DrawState *ds );
void polygon_drawFill(Polygon *p, Image *src, Color c);

void polygon_drawFillGradient(Polygon *p, Image *src, Color c1, Color c2, Point a, Point b );

// draw the filled polygon using color c with the Barycentric coordinates algorithm.
void polygon_drawFillB(Polygon *p, Image *src, Color c);

void polygon_drawFillBGradient(Polygon *p, Image *src, Color c1, Color c2, Color c3);

void polygon_shade(Polygon *p, Lighting *lighting, DrawState *ds);

// draw the filled polygon using the given DrawState. The shade field of the DrawState 
// determines how the polygon should be rendered. The Lighting parameter should be NULL 
// unless you are doing Phong shading
// void polygon_drawShade(Polygon *p, Image *src, DrawState *ds, Lighting *light);

void polygon_setNormals(Polygon *p, int numV, Vector *nlist);

#endif