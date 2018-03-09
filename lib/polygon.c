#include "polygon.h"

  int oneSided; // whether to consider the polygon one-sided (1) or two-sided (0) for shading
  int nVertex;
  Point *vertex;  // vertex information
  Color *color;  //  color information for each vertex
  Vector *normal; //  surface normal information for each vertex.
  int zBuffer;

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
  p->normal = NULL;
  p->oneSided = 1;
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
  p->normal = NULL;
  p->oneSided = 1;
  
  return pline;
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
  if (p->normal) {
    free(p->normal);
    p->normal = NULL;
  }
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
  p->normal = NULL;
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
  p->normal = NULL;
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
  if (p->normal) {
    free(p->normal);
    p->normal = NULL;
  }
  
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
  
  p->colors = malloc(sizeof(Color) * numV);
  
  if (!p->colors) {
    printf("Ran out of memory while mallocing colors pointer in polygon_setColors!\n");
    exit(-1);
  }
  
  int i;
  for (i=0; i<numV; i++) {
    p->colors[i] = clist[i];
  }
}

void polygon_setNormals(Polygon *p, int numV, Vector *nlist) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polygon_setNormals!\n");
    exit(-1);    
  }
  
  p->normal = malloc(sizeof(Vector) * numV);
  
  if (!p->normal) {
    printf("Ran out of memory while mallocing normals pointer in polygon_setNormals!\n");
    exit(-1);
  }
  
  int i;
  for (i=0; i<numV; i++) {
    p->normal[i] = nlist[i];
  }
}

void polygon_setAll(Polygon *p, int numV, Point *vlist, Color *clist, Vector *nlist, int zBuffer, int oneSided) {
  if (numV < 0) {
    printf("numVertex cannot be negative in polygon_setNormals!\n");
    exit(-1);    
  }
  
  p->vertex = malloc(sizeof(Point) * numV);
  p->normal = malloc(sizeof(Vector) * numV);
  p->colors = malloc(sizeof(Color) * numV);
  
  if (!p->vertex || !p->normal || !p->colors) {
    printf("Ran out of memory while mallocing in polygon_setAll!\n");
    exit(-1);
  }
  
  int i;
  for (i=0; i<numV; i++) {
    p->vertex[i] = vlist[i];
    p->normal[i] = nlist[i];
    p->colors[i] = clist[i];
  }
  
  p->zBuffer = zBuffer;
  p->nVertex = numV;
  p->oneSided = oneSided;
}

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
  for (i=0; i<p->numVertex; i++) {
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
  int numVertex = p->numVertex;
  Line line;
  
  // connect all points except for first and last
  for (i=0; i<numVertex-1; i++) {
    line_set(&line, p->vertex[i], p->vertex[i+1]);
    line_draw(&line, src, c);
  }
  
  // connect first and last points
  line_set(&line, p->vertex[0], p->vertex[i+1]);
  line_draw(&line, src, c);
  
}

void polygon_drawFill(Polygon *p, Image *src, Color c) {

}

