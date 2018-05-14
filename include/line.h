#ifndef LINE_H

#define LINE_H

#define line_set(line, s, e)({\
  (line)->a = (s);\
  (line)->b = (e);\
})

// #define mult_2(a)(a<<1)

#include <stdio.h>
#include "image.h"
#include "color.h"

typedef struct {
  double val[4]; // [x, y, z, h]
} Point;

typedef struct {
  double zBuffer;
  Point a;
  Point b;
} Line;

typedef struct {
  double zBuffer;
  int numVertex;
  Point *vertex;
} Polyline;

void EFLA(Line *line, Image *src, Color color);

Point point_create2D(double x, double y);

void point_set2D(Point *point, double x, double y);

void point_set3D(Point *point, double x, double y, double z);

void point_setFraction(Point *point, Point *p1, Point *p2, float u);

void point_set(Point *p, double x, double y, double z, double h);

void point_normalize(Point *point);

void point_copy(Point *to, Point *from);

void point_draw(Point *p, Image *src, Color color);

void point_drawf(Point *p, Image *src, FPixel c);

void point_print(Point *p, FILE *fp);

void line_set2D(Line *line, double x1, double y1, double x2, double y2);

// void line_set(Line *line, Point start, Point end);

void line_zBuffer(Line *l, double flag);

void line_normalize(Line *l);

void line_copy(Line *to, Line *from);

void line_print(Line *line, FILE *fp);

void line_draw(Line *line, Image *src, Color color);

void line_drawRef(Line *line, Image *src, Color *color);

void line_draw_spaced(Line *line, Image *src, Color color, int interval);

void line_draw_aa(Line *line, Image *src, Color color);

Polyline *polyline_create(void);

Polyline *polyline_createp( int numV, Point *vlist );

void polyline_free(Polyline *p);

void polyline_init( Polyline *pLine );

void polyline_set( Polyline *pLine, int numVertex, Point *point );

void polyline_clear( Polyline *pLine );

void polyline_zBuffer(Polyline *p, double flag);

void polyline_copy(Polyline *to, Polyline *from);

void polyline_print(Polyline *p, FILE *fp);

void polyline_normalize( Polyline *p );

void polyline_draw( Polyline *pLine, Image *src, Color color);



#endif