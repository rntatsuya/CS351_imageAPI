#ifndef LINE_H

#define LINE_H


#include <stdio.h>
#include "image.h"
#include "color.h"

typedef struct {
  int oneSided; // whether to consider the polygon one-sided (1) or two-sided (0) for shading
  int nVertex;
  Point *vertex;  // vertex information
  Color *color;  //  color information for each vertex
  Vector *normal; //  surface normal information for each vertex.
  int zBuffer;
} Polyline;

// returns an allocated Polygon pointer initialized 
// so that numVertex is 0 and vertex is NULL.
Polygon *polygon_create();

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
void polygon_setNormals(Polygon *p, int numV, Vector *nlist);

// initializes the vertex list to the points in vlist, the colors to the colors in clist, 
// the normals to the vectors in nlist, and the zBuffer and oneSided flags 
// to their respectively values.
void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, Vector *nlist, int zBuffer, int oneSided);

// sets the z-buffer flag to the given value.
void polygon_zBuffer(Polygon *p, int flag);

// De-allocates/allocates space and copies the vertex and color data from one polygon to the other.
void polygon_copy(Polygon *to, Polygon *from)

// prints polygon data to the stream designated by the FILE pointer.
void polygon_print(Polygon *p, FILE *fp);

// normalize the x and y values of each vertex by the homogeneous coord.
void polygon_normalize( Polygon *p );

// draw the outline of the polygon using color c.
void polygon_draw(Polygon *p, Image *src, Color c);

// draw the filled polygon using color c with the scanline z-buffer rendering algorithm.
void polygon_drawFill(Polygon *p, Image *src, Color c);

// draw the filled polygon using color c with the Barycentric coordinates algorithm.
void polygon_drawFillB(Polygon *p, Image *src, Color c);

// draw the filled polygon using the given DrawState. The shade field of the DrawState 
// determines how the polygon should be rendered. The Lighting parameter should be NULL 
// unless you are doing Phong shading
void polygon_drawShade(Polygon *p, Image *src, DrawState *ds, Lighting *light);

#endif