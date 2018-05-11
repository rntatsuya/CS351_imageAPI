/**
 * Kimberly and Tatsuya
 * module.c
 */

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>


void drawTriangle( Module *mod, Point a, Point b, Point c );
Point getMidPoint( Point p1, Point p2 );
void subdivide( Module *mod, Point p1, Point p2, Point p3, int lvl );
Point getMidPoint2( Point p1, Point p2 );
void subdivide2( Module *mod, Point p1, Point p2, Point p3, int lvl );

////////////////////////////////////////
// General Module + Element Functions //
////////////////////////////////////////

Element *element_create( void ) {
	Element *e = malloc(sizeof(Element));
	
	if (!e) {
    	printf("Ran out of memory while mallocing Element pointer in element_create!\n");
    	exit(-1);
	}
	
	e->type = ObjNone;
	e->obj = (Object)NULL; 
	e->next = NULL;
	
	return e;
}

Element *element_init( ObjectType type, void *obj ) {
	Element *e = malloc(sizeof(Element));
	
	if (!e) {
    	printf("Ran out of memory while mallocing Element pointer in element_create!\n");
    	exit(-1);
	}

	// make copy of original obj
	Object copyObj;

	switch (type) {
		case ObjNone :
			{
				copyObj = (Object)NULL;
				break;
			}
		
		case ObjPoint :
			{
				point_copy( &copyObj.point, obj );
				break;
			}
		
		case ObjLine :
			{
				line_copy( &copyObj.line, obj );
				break;
			}
			
		case ObjPolyline :
			{
				polyline_copy( &copyObj.polyline, obj);
				break;
			}
		
		case ObjPolygon :
			{
// 				printf("in element_init, copying polygon\n");
				polygon_copy( &copyObj.polygon, obj);
				break;
			}
		
		case ObjIdentity :
			{
				matrix_identity( &copyObj.matrix );
				break;
			}
		
		case ObjMatrix :
			{
				matrix_copy( &copyObj.matrix, obj );
				break;
			}

		case ObjColor :
			{
				color_set( &copyObj.color, 
					((Color *)obj)->c[0], 
					((Color *)obj)->c[1], 
					((Color *)obj)->c[2] );
				break;
			}
		
		case ObjBodyColor :
			{
				color_set( &copyObj.color, 
					((Color *)obj)->c[0], 
					((Color *)obj)->c[1], 
					((Color *)obj)->c[2] );
				break;
			}
		
		case ObjSurfaceColor :
			{
				color_set( &copyObj.color, 
					((Color *)obj)->c[0], 
					((Color *)obj)->c[1], 
					((Color *)obj)->c[2] );
				break;
			}
		
		case ObjSurfaceCoeff :
			{
				copyObj.coeff = *(float*)obj; 
				break;
			}
		
		case ObjLight :
			{
				copyObj = (Object)NULL; 
				break;
			}

		case ObjModule :
			{
				// No duplicate module needed
				copyObj.module = obj;
				break;
			}
	}
	
	e->type = type;
	e->next = NULL; 
	e->obj = copyObj;
	
	return e;
}

void element_delete( Element *e ) {
	// Free element and object it contains
	switch(e->type) {
		case ObjNone:
			// Not sure what to free here
			break;
		
		case ObjPoint:
			{
				free(&(e->obj.point));
				break;
			}
		
		case ObjLine:
			{
				free(&(e->obj.line));
				break;
			}
		
		case ObjPolyline:
			{
				polyline_clear(&(e->obj.polyline));
				break;
			}
		
		case ObjPolygon:
			{
				polygon_clear(&(e->obj.polygon));
				break;
			}
		
		case ObjIdentity: case ObjMatrix:
			{
				free(&(e->obj.matrix));
				break;
			}
		
		case ObjColor: case ObjBodyColor: case ObjSurfaceColor:
			{
				free(&(e->obj.color));
				break;
			}
		
		case ObjSurfaceCoeff:
			{
				free(&(e->obj.coeff));
				break;
			}
		
		case ObjLight:
			{
				// if (e->obj.polyline) 
					// No light property in Object 
					// free(e->obj.light);
				break;
			}

		case ObjModule:
			{
				free(&(e->obj.module));
				break;
			}
	}

	if (e) 
		free(e);
}

Module *module_create( void ) {
	Module *md = malloc(sizeof(Module));
	
	md->head = NULL;
	md->tail = NULL;
	
	return md;
}

void module_clear( Module *md ) {
	Element *cur_e = md->head;
	Element *temp;
	
	// loop till we get a NULL for the next pointer
	while (cur_e->next) {
		temp = cur_e;
		
		
		cur_e = temp->next;
	}
}

void module_delete( Module *md ) {
	// Free memory associated with module (including memory pointed to by md)
	Element *temp;
	Element *cur_e = md->head;

	while ( cur_e ) {
		temp = cur_e->next;
		free(cur_e);
		cur_e = temp;
	}

	free(md);
	return;
}

void module_insert( Module *md, Element *e ) {
	if (!md->head) {
		md->head = e;
		md->tail = e;
		return;
	}

	Element *cur_e = md->head;
	
// 	printf("in module_insert, going to traverse down\n");
	// loop till we get a NULL for the next pointer
	while (cur_e->next) {
		cur_e = cur_e->next;
	}
	
// 	printf("in module_insert, setting last element in md to new element\n");
	cur_e->next = e;
	md->tail = e;
}

void module_module( Module *md, Module *sub ) {
	Element *e;
	e = element_init( ObjModule, sub );

	module_insert( md, e );
}

void module_point( Module *md, Point *p ) {
	Element *e;
	e = element_init( ObjPoint, p );

	module_insert( md, e );
}

void module_line( Module *md, Line *p ) {
	Element *e;
	e = element_init( ObjLine, p );
	
	module_insert( md, e );
}

void module_polyline( Module *md, Polyline *p ) {
	Element *e;
	e = element_init( ObjPolyline, p );

	module_insert( md, e );
}

void module_polygon( Module *md, Polygon *p ) {
	Element *e;
// 	printf("in module_polygon, initializing e\n");
	e = element_init( ObjPolygon, p );
	
// 	printf("in module_polygon, inserting e into md\n");
	module_insert( md, e );
}

void module_identity( Module *md ) {
	Element *e;
	Matrix m;

	matrix_identity( &m );
	e = element_init( ObjIdentity, &m );

	module_insert( md, e );
}

void module_color(Module *md, Color *c) { 
	// Adds fg color value to tail of module LL
	Element *e;
	Color tempColor;

	color_set( &tempColor, c->c[0], c->c[1], c->c[2] );
	e = element_init( ObjColor, &tempColor );

	module_insert( md, e );
}

void module_bezierCurve(Module *md, BezierCurve *b, int divisions) {
	printf("divisions %d\n", divisions);
	if (divisions == 0) {
		// no more subdivisions, just connect the control points
		Line l;
		
		line_set2D(&l, b->cpt[0].val[0], b->cpt[0].val[1], b->cpt[1].val[0], b->cpt[1].val[1]);
		module_line( md, &l );
		line_set2D(&l, b->cpt[1].val[0], b->cpt[1].val[1], b->cpt[2].val[0], b->cpt[2].val[1]);
		module_line( md, &l );
		line_set2D(&l, b->cpt[2].val[0], b->cpt[2].val[1], b->cpt[3].val[0], b->cpt[3].val[1]);
		module_line( md, &l );
		return;
	}
	
	// create two new bezier curves from original
	BezierCurve b1;
	BezierCurve b2;
	Point p[7];
	Point p_n[7];
	float u = 0.5;
	int i;
	
	// P0 
	point_copy(&p[0], &b->cpt[0]);
	// P1
	point_copy(&p[2], &b->cpt[1]);
	// P2
	point_copy(&p[4], &b->cpt[2]);
	// P3
	point_copy(&p[6], &b->cpt[3]);
	// point between P0 and P1 => F0
	point_setFraction(&p[1], &p[0], &p[2], u);
	// point between P1 and P2 => F1
	point_setFraction(&p[3], &p[2], &p[4], u);
	// point between P2 and P3 => F2
	point_setFraction(&p[5], &p[4], &p[6], u);

	// P0 => A0
	point_copy(&p_n[0], &p[0]);
	// F1 => A1
	point_copy(&p_n[1], &p[1]);
	// between A1 and F1 => A2
	point_setFraction(&p_n[2], &p_n[1], &p[3], u);
	// start making points from other side 
	// P3 => B3
	point_copy(&p_n[6], &p[6]);
	// F2 => B2
	point_copy(&p_n[5], &p[5]);
	// between B2 and F1 => B1
	point_setFraction(&p_n[4], &p_n[5], &p[3], u);
	// between A2 and B1 => A3 & B0
	point_setFraction(&p_n[3], &p_n[4], &p_n[2], u);
	
	printf("Original Points\n");
	for (i=0; i<4; i++) {
		point_print(&b->cpt[i], stdout);
	}
	printf("Original + Half Points\n");
	for (i=0; i<7; i++) {
		point_print(&p[i], stdout);
	}
	printf("Subdivided Points\n");
	for (i=0; i<7; i++) {
		point_print(&p_n[i], stdout);
	}

	bezierCurve_set( &b1, &p_n[0] );
	bezierCurve_set( &b2, &p_n[3] );	
	module_bezierCurve(md, &b1, divisions-1);
	module_bezierCurve(md, &b2, divisions-1);
}

void module_bezierSurface(Module *md, BezierSurface *b, int divisions, int solid) {
	printf("divisions %d\n", divisions);
	if (divisions == 0) {
		// no more subdivisions, just connect the control points
		Polygon poly;
		// make vlist with only the 4 corners of the control points
		Point p[4];
		int i,j;
		
		for (i=0; i<3; i++) {
			for (j=0; j<3; j++) {
				p[0] =  b->cpt[i*4+j];
				p[1] =  b->cpt[i*4+j+1];
				p[2] =  b->cpt[(i+1)*4+j+1];
				p[3] =  b->cpt[(i+1)*4+j];

				// make two triangles
// 				polygon_set(&poly, 3, &p[0]);
// 				module_polygon( md, &poly );
// 				polygon_set(&poly, 3, &p[1]);
// 				module_polygon( md, &poly );
				
				// make a quadralateral
				polygon_set(&poly, 4, &p[0]);
				printf("Adding polygon: ");
				polygon_print(&poly, stdout);
				module_polygon( md, &poly );

			}
		}
		printf("division %d is done\n", divisions);
		return;
	}
	
	// create four new bezier surfaces by subdivision
	BezierSurface b1;
	Point p[49];
	Point vlist[16];
	float u = 0.5;
	int base_idx, i,j,k,l,m;
	
	// subdivide points horizontally
	for (i=0; i<4; i++) {
		for (j=0; j<3; j++) {
			printf("p[%d] from b->cpt[%d]\n", i*14 + j*2, i*4+j);
			printf("p[%d] from half of b->cpt[%d] and b->cpt[%d]\n", i*14 + j*2+1, i*4+j, i*4+j+1);
			point_copy(&p[i*14 + j*2], &b->cpt[i*4+j]);
			point_setFraction(&p[i*14 + j*2+1], &b->cpt[i*4+j], &b->cpt[i*4+j+1], u);
		}
		printf("Last col: p[%d] from b->cpt[%d]\n", i*14 + j*2, i*4+j);
		point_copy(&p[i*14 + j*2], &b->cpt[i*4+j]);// make sure we get the last column
		
	}
	
	// subdivide points vertically 
	for (i=0; i<3; i++) { // don't do last row
		for (j=0; j<3; j++) { 
			printf("p[%d] from half of b->cpt[%d] and b->cpt[%d]\n", i*14 + j*2+7, i*4+j, (i+1)*4+j);
			printf("p[%d] from half of p[%d] and p[%d]\n", i*14 + j*2+1+7, i*14 + j*2+1, (i+1)*14 + j*2+1);
			point_setFraction(&p[i*14 + j*2+7], &b->cpt[i*4+j], &b->cpt[(i+1)*4+j], u);
			point_setFraction(&p[i*14 + j*2+1+7], &p[i*14 + j*2+1], &p[(i+1)*14 + j*2+1], u);
		}
		printf("Last col: p[%d] from half of b->cpt[%d] and b->cpt[%d]\n", i*14 + j*2+7, i*4+j, (i+1)*4+j);
		point_setFraction(&p[i*14 + j*2+7], &b->cpt[i*4+j], &b->cpt[(i+1)*4+j], u);// make sure we get the last column
	}
	
	// make 16 point vlist 4 times
	for (i=0; i<2; i++) {
		for (j=0; j<2; j++) {
			base_idx = i*21 + j*3;
			for (k=0; k<4; k++) {
				for (l=0; l<4; l++) {
					printf("vlist[%d] = p[%d]\n", k*4+l, base_idx+k*7+l);
					vlist[k*4+l] = p[base_idx+k*7+l];
				}
			}
			
			printf("\nOriginal Points\n");
			for (m=0; m<16; m++) {
				printf("b->cpt[%d] is ", m);
				point_print(&b->cpt[m], stdout);
			}
// 			printf("Original + Half Points\n");
// 			for (i=0; i<7; i++) {
// 				point_print(&p[i], stdout);
// 			}
			printf("Subdivided Points\n");
			for (m=0; m<16; m++) {
				printf("vlist[%d] is ", m);
				point_print(&vlist[m], stdout);
			}
			
			bezierSurface_set( &b1, &vlist[0] );
			module_bezierSurface(md, &b1, divisions-1, solid);
			printf("Done with surface %d\n", i*2+j);
		}
	}
	printf("division %d is done\n", divisions);
}

/////////////////////////
// 2D Module Functions //
/////////////////////////

void module_translate2D( Module *md, double tx, double ty ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_translate2D( &m, tx, ty );
	e = element_init( ObjMatrix, &m );

	// printf("module translate %f %f\n", tx, ty);
	// matrix_print( &m, stdout );

	module_insert( md, e );
}

void module_scale2D( Module *md, double sx, double sy ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_scale2D( &m, sx, sy );
	e = element_init( ObjMatrix, &m );

	// printf("module scaling %f %f\n", sx, sy);
	// matrix_print( &m, stdout );
	
	module_insert( md, e );
}

void module_rotateZ( Module *md, double cth, double sth ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_rotateZ( &m, cth, sth );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_shear2D( Module *md, double shx, double shy ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_shear2D( &m, shx, shy );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_draw( Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src ) {
	Matrix LTM;
	matrix_identity( &LTM );
	
	Element *cur_e = md->head;
	
	
	while ( cur_e ) { // Break when pointer reaches end of LL
		printf("Drawing type %d\n", cur_e->type);
		
		switch( cur_e->type ) {
			case ObjColor:
				{
					ds->color = cur_e->obj.color;
					break;
				}

			case ObjPoint:
				{
					Point temp1, temp2;
					matrix_xformPoint( &LTM, &(cur_e->obj.point), &temp1 );
					matrix_xformPoint( GTM, &temp1, &temp2 );
					matrix_xformPoint( VTM, &temp2, &temp1 );
					point_normalize( &temp1 );
					point_print( &temp1, stdout );
					point_draw( &temp1, src, ds->color );
					point_print( &temp1, stdout );
					break;
				}

			case ObjLine:
				{
					line_print(&(cur_e->obj.line), stdout);
					Line temp;
					line_copy( &temp, &(cur_e->obj.line) );
					matrix_xformLine( &LTM, &temp );
					matrix_xformLine( GTM, &temp );
					matrix_xformLine( VTM, &temp );
					line_normalize( &temp );
					line_draw( &temp, src, ds->color );
// 					line_print( &temp, stdout );
					break;
				}

			case ObjPolygon:
				{
					Polygon temp;
					polygon_copy( &temp, &(cur_e->obj.polygon) );
					matrix_xformPolygon( &LTM, &temp );
					matrix_xformPolygon( GTM, &temp );
					matrix_xformPolygon( VTM, &temp );
					polygon_normalize( &temp );

					printf("Drawing polygon at: ");
					polygon_print(&temp, stdout);					
					polygon_drawShade(&temp, src, ds, lighting);

					break;
				}

			case ObjMatrix:
				{
					matrix_multiply( &(cur_e->obj.matrix), &LTM, &LTM ); 
					break;
				}

			case ObjIdentity:
				{
					matrix_identity( &LTM );
					break;
				}

			case ObjModule:
				{
					Matrix tempGTM;
					matrix_multiply( GTM, &LTM, &tempGTM );
					
					DrawState tempDS;
					
					drawstate_copy( &tempDS, ds );

					module_draw( cur_e->obj.module, VTM, &tempGTM, &tempDS, lighting, src );
					break;
				}

			default:
				break;
		}

		// Move pointer to next element in LL 
// 		printf("moving pointer to next element\n");
		cur_e = cur_e->next; 
	}
// 	printf("done\n");
}


/////////////////////////
// 3D Module Functions //
/////////////////////////

void module_translate( Module *md, double tx, double ty, double tz ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_translate( &m, tx, ty, tz );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_scale( Module *md, double sx, double sy, double sz ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_scale( &m, sx, sy, sz );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_rotateX( Module *md, double cth, double sth ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_rotateX( &m, cth, sth );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_rotateY( Module *md, double cth, double sth ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_rotateY( &m, cth, sth );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

void module_rotateXYZ( Module *md, Vector *u, Vector *v, Vector *w ) {
	Element *e;
	Matrix m;
	matrix_identity(&m);

	matrix_rotateXYZ( &m, u, v, w );
	e = element_init( ObjMatrix, &m );

	module_insert( md, e );
}

/////////////////////
// Unit Primitives //
/////////////////////

/**
 * Code from Bruce
 */
void module_cube( Module *md, int solid ) {
	// Point pt[4];
	// Polygon p;

	// polygon_init( &p );
	// point_set3D( &pt[0], -1, -1, -1 );
	// point_set3D( &pt[1], -1, -1,  1 );
	// point_set3D( &pt[2], -1,  1,  1 );
	// point_set3D( &pt[3], -1,  1, -1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );

	// point_set3D( &pt[0], 1, -1, -1 );
	// point_set3D( &pt[1], 1, -1,  1 );
	// point_set3D( &pt[2], 1,  1,  1 );
	// point_set3D( &pt[3], 1,  1, -1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );

	// point_set3D( &pt[0], -1, -1, -1 );
	// point_set3D( &pt[1], -1, -1,  1 );
	// point_set3D( &pt[2],  1, -1,  1 );
	// point_set3D( &pt[3],  1, -1, -1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );

	// point_set3D( &pt[0], -1, 1, -1 );
	// point_set3D( &pt[1], -1, 1,  1 );
	// point_set3D( &pt[2],  1, 1,  1 );
	// point_set3D( &pt[3],  1, 1, -1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );

	// point_set3D( &pt[0], -1, -1, -1 );
	// point_set3D( &pt[1], -1,  1, -1 );
	// point_set3D( &pt[2],  1,  1, -1 );
	// point_set3D( &pt[3],  1, -1, -1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );

	// point_set3D( &pt[0], -1, -1, 1 );
	// point_set3D( &pt[1], -1,  1, 1 );
	// point_set3D( &pt[2],  1,  1, 1 );
	// point_set3D( &pt[3],  1, -1, 1 );
	// polygon_set( &p, 4, pt );
	// module_polygon( md, &p );
}

/**
 * Code from Bruce
 */
void module_cylinder( Module *mod, int sides ) {

	if (sides < 3) {
		printf("Please specify subdivision greater than or equal to 3 for a cylinder\n");
		exit(-1);
	}

	Polygon p;
	Point xtop, xbot;
	double x1, x2, z1, z2;
	int i;

	polygon_init( &p );
	point_set3D( &xtop, 0, 1.0, 0.0 );
	point_set3D( &xbot, 0, 0.0, 0.0 );

	// make a fan for the top and bottom sides
	// and quadrilaterals for the sides
	for(i=0;i<sides;i++) {
		Point pt[4];

		x1 = cos( i * M_PI * 2.0 / sides );
		z1 = sin( i * M_PI * 2.0 / sides );
		x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
		z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

		point_copy( &pt[0], &xtop );
		point_set3D( &pt[1], x1, 1.0, z1 );
		point_set3D( &pt[2], x2, 1.0, z2 );

		polygon_set( &p, 3, pt );
		module_polygon( mod, &p );

		point_copy( &pt[0], &xbot );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );

		polygon_set( &p, 3, pt );
		module_polygon( mod, &p );

		point_set3D( &pt[0], x1, 0.0, z1 );
		point_set3D( &pt[1], x2, 0.0, z2 );
		point_set3D( &pt[2], x2, 1.0, z2 );
		point_set3D( &pt[3], x1, 1.0, z1 );

		polygon_set( &p, 4, pt );
		module_polygon( mod, &p );
	}

	polygon_clear( &p );
}

void module_pyramid( Module *mod, int sides ) {
	if (sides < 3) {
		printf("Please specify subdivision greater than or equal to 3 for a pyramid\n");
		exit(-1);
	}

	Polygon p, b;
	Point top;
	Point basePt[sides];
	double x1, x2, z1, z2;
	int i;

	polygon_init( &p );
	point_set3D( &top, 0.0, 1.0, 0.0 );

	for(i=0;i<sides;i++) {
		Point pt[4];

		// Generate 2 base points of pyramid face
		x1 = cos( i * M_PI * 2.0 / sides );
		z1 = sin( i * M_PI * 2.0 / sides );
		x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
		z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

		// Add point to base polygon 
		point_set3D( &basePt[i], x1, 0.0, z1 );

		// Create one face of pyramid
		point_copy( &pt[0], &top );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );
		polygon_set( &p, 3, pt );
		module_polygon( mod, &p );
	}

	// Create base of pyramid
	polygon_set( &b, sides, basePt );
	module_polygon( mod, &b );

	// Clean up
	polygon_clear( &p );
	polygon_clear( &b );
}

void drawTriangle( Module *mod, Point a, Point b, Point c ) {
	Point pt[3];
	Polygon p; 
	point_copy( &pt[0], &a );
	point_copy( &pt[1], &b );
	point_copy( &pt[2], &c );
	polygon_set( &p, 3, &pt );
	module_polygon( mod, &p );
}

Point *buildIcosahedron( Module *mod ) {
	// Golden ratio
	float t = (1 +sqrt(5))/ 2;
	int size = 1; 
	Polygon p;
	Point *vList[12]; 

	// Define 12 points on icosahedron 
	Point pt[12];
	point_set3D( &pt[0], -size, t*size, 0 );
	point_set3D( &pt[1], size, t*size, 0 );
	point_set3D( &pt[2], -size, -t*size, 0 );
	point_set3D( &pt[3], size, -t*size, 0 );
	point_set3D( &pt[4], 0, -size, t*size );
	point_set3D( &pt[5], 0, size, t*size );
	point_set3D( &pt[6], 0, -size, -t*size );
	point_set3D( &pt[7], 0, size, -t*size );
	point_set3D( &pt[8], t*size, 0, -size );
	point_set3D( &pt[9], t*size, 0, size );
	point_set3D( &pt[10], -t*size, 0, -size );
	point_set3D( &pt[11], -t*size, 0, size );

	// Add points to list of vertices 
	for ( size = 0; size < 12; size++ ) {
		point_copy( vList[size], &pt[size] );
	}

	// 5 faces around point 0
	drawTriangle( mod, pt[0], pt[11], pt[5] );
	drawTriangle( mod, pt[0], pt[5], pt[1] );
	drawTriangle( mod, pt[0], pt[1], pt[7] );
	drawTriangle( mod, pt[0], pt[7], pt[10] );
	drawTriangle( mod, pt[0], pt[10], pt[11] );

	// 5 adjacent faces
	drawTriangle( mod, pt[1], pt[5], pt[9] );
	drawTriangle( mod, pt[5], pt[11], pt[4] );
	drawTriangle( mod, pt[11], pt[10], pt[2] );
	drawTriangle( mod, pt[10], pt[7], pt[6] );
	drawTriangle( mod, pt[7], pt[1], pt[8] );

	// 5 faces around point 3
	drawTriangle( mod, pt[3], pt[9], pt[4] );
	drawTriangle( mod, pt[3], pt[4], pt[2] );
	drawTriangle( mod, pt[3], pt[2], pt[6] );
	drawTriangle( mod, pt[3], pt[6], pt[8] );
	drawTriangle( mod, pt[3], pt[8], pt[9] );

	// 5 adjacent faces
	drawTriangle( mod, pt[4], pt[9], pt[5] );
	drawTriangle( mod, pt[2], pt[4], pt[11] );
	drawTriangle( mod, pt[6], pt[2], pt[10] );
	drawTriangle( mod, pt[8], pt[6], pt[7] );
	drawTriangle( mod, pt[9], pt[8], pt[1]) ;	

	return vList;
}

/**
 * Get midpoint between 2 points and normalize
 */
Point getMidPoint( Point p1, Point p2 ) {
	Point midPt;
	point_set3D( &midPt, 
		(p2.val[0]+p1.val[0])*0.5,
		(p2.val[1]+p1.val[1])*0.5,
		(p2.val[2]+p1.val[2])*0.5 );

	// Offset point using normalized vector of midPoint 
	double l = sqrt( 
		midPt.val[0]*midPt.val[0]+
		midPt.val[1]*midPt.val[1]+
		midPt.val[2]*midPt.val[2] );

	point_set3D( &midPt, 
		midPt.val[0]/l,
		midPt.val[1]/l,
		midPt.val[2]/l );

	return midPt;
}

/**
 * Helper function for subdivision
 */
void subdivide( Module *mod, Point p1, Point p2, Point p3, int lvl ) {
	if ( lvl == 0 ) {
		drawTriangle( mod, p1, p2, p3 );
		return;
	} else {
		int i;
		Point mp12, mp23, mp31;
		mp12 = getMidPoint( p1, p2 );
		mp23 = getMidPoint( p2, p3 );
		mp31 = getMidPoint( p3, p1 );

		subdivide( mod, p1, mp12, mp31, lvl-1 );
		subdivide( mod, p2, mp23, mp12, lvl-1 );
		subdivide( mod, p3, mp31, mp23, lvl-1 );
		subdivide( mod, mp12, mp23, mp31, lvl-1 );
	}
}

void module_sphere( Module *mod, int lvl ) {
	Polygon p;
	Point top, btm;
	double x1, x2, z1, z2;
	int i, sides = 4;

	polygon_init( &p );
	point_set3D( &top, 0.0, 1.0, 0.0 );
	point_set3D( &btm, 0.0, -1.0, 0.0 );

	for ( i = sides; i > 0; i-- ) {
		Point pt[3];
		x1 = cos( i * M_PI * 2.0 / sides );
		z1 = sin( i * M_PI * 2.0 / sides );
		x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
		z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

		// Create upper half
		point_copy( &pt[0], &top );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );
		subdivide( mod, pt[0], pt[1], pt[2], lvl );
		
		// Create bottom half
		point_copy( &pt[0], &btm );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );
		subdivide( mod, pt[0], pt[1], pt[2], lvl );
	}
}

/**
 * Get midpoint between 2 points and normalize
 */
Point getMidPoint2( Point p1, Point p2 ) {
	Point midPt;
	
	//The golden ratio
	float t = (1 + sqrt(5)) / 2;

	point_set3D( &midPt, 
		(p2.val[0]+p1.val[0])*0.5,
		(p2.val[1]+p1.val[1])*0.5,
		(p2.val[2]+p1.val[2])*0.5 );

	// Normalize using homogenous coordinate
	point_normalize( &midPt );
	
	// To get other random shape
	int size = 3; 
	midPt.val[0] *= sqrt(t*t+1)*size;
	midPt.val[1] *= sqrt(t*t+1)*size;
	midPt.val[2] *= sqrt(t*t+1)*size;

	return midPt;
}

/**
 * Helper function for subdivision
 */
void subdivide2( Module *mod, Point p1, Point p2, Point p3, int lvl ) {
	if ( lvl == 0 ) {
		drawTriangle( mod, p1, p2, p3 );
		return;
	} else {
		int i;
		Point mp12, mp23, mp31;
		mp12 = getMidPoint2( p1, p2 );
		mp23 = getMidPoint2( p2, p3 );
		mp31 = getMidPoint2( p3, p1 );

		subdivide2( mod, p1, mp12, mp31, lvl-1 );
		subdivide2( mod, p2, mp23, mp12, lvl-1 );
		subdivide2( mod, p3, mp31, mp23, lvl-1 );
		subdivide2( mod, mp12, mp23, mp31, lvl-1 );
	}
}

void module_sphere2( Module *mod, int lvl ) {
	Polygon p;
	Point top, btm;
	double x1, x2, z1, z2;
	int i, sides = 4;

	polygon_init( &p );
	point_set3D( &top, 0.0, 1.0, 0.0 );
	point_set3D( &btm, 0.0, -1.0, 0.0 );

	for ( i = sides; i > 0; i-- ) {
		Point pt[3];
		x1 = cos( i * M_PI * 2.0 / sides );
		z1 = sin( i * M_PI * 2.0 / sides );
		x2 = cos( ( (i+1)%sides ) * M_PI * 2.0 / sides );
		z2 = sin( ( (i+1)%sides ) * M_PI * 2.0 / sides );

		// Create upper half
		point_copy( &pt[0], &top );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );
		subdivide2( mod, pt[0], pt[1], pt[2], lvl );
		
		// Create bottom half
		point_copy( &pt[0], &btm );
		point_set3D( &pt[1], x1, 0.0, z1 );
		point_set3D( &pt[2], x2, 0.0, z2 );
		subdivide2( mod, pt[0], pt[1], pt[2], lvl );
	}
}