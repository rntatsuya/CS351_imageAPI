/**
 * Kimberly and Tatsuya
 * module.c
 */

#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>

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
	point_set2D(&p[0], b->cpt[0].val[0], b->cpt[0].val[1]); 
	// P1
	point_set2D(&p[2], b->cpt[1].val[0], b->cpt[1].val[1]);
	// P2
	point_set2D(&p[4], b->cpt[2].val[0], b->cpt[2].val[1]);
	// P3
	point_set2D(&p[6], b->cpt[3].val[0], b->cpt[3].val[1]);
	// point between P0 and P1 => F0
	point_set2D(&p[1], ret_frac(p[0].val[0], p[2].val[0], u), ret_frac(p[0].val[1], p[2].val[1], u));
	// point between P1 and P2 => F1
	point_set2D(&p[3], ret_frac(p[2].val[0], p[4].val[0], u), ret_frac(p[2].val[1], p[4].val[1], u));
	// point between P2 and P3 => F2
	point_set2D(&p[5], ret_frac(p[4].val[0], p[6].val[0], u), ret_frac(p[4].val[1], p[6].val[1], u));

	// P0 => A0
	point_copy(&p_n[0], &p[0]);
	// F1 => A1
	point_copy(&p_n[1], &p[1]);
	// between A1 and F1 => A2
	point_set2D(&p_n[2], ret_frac(p_n[1].val[0], p[3].val[0], u),  ret_frac(p_n[1].val[1], p[3].val[1], u));
	// start making points from other side 
	// P3 => B3
	point_copy(&p_n[6], &p[6]);
	// F2 => B2
	point_copy(&p_n[5], &p[5]);
	// between B2 and F1 => B1
	point_set2D(&p_n[4], ret_frac(p_n[5].val[0], p[3].val[0], u),  ret_frac(p_n[5].val[1], p[3].val[1], u));
	// between A2 and B1 => A3 & B0
	point_set2D(&p_n[3], ret_frac(p_n[4].val[0], p_n[2].val[0], u),  ret_frac(p_n[4].val[1], p_n[2].val[1], u));
	
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

void module_bezierSurface(Module *m, BezierSurface *b, int divisions, int solid) {
	printf("divisions %d\n", divisions);
	if (divisions == 0) {
		// no more subdivisions, just connect the control points
		Polygon p;
		// make vlist with only the 4 corners of the control points
		Point p[4];
		p[0] =  b->cpt[0];
		p[1] =  b->cpt[3];
		p[2] =  b->cpt[12];
		p[3] =  b->cpt[15];
		
		// make two triangles
		polygon_set(&p, 3, &p[0])
		module_line( md, &p );
		polygon_set(&p, 3, &p[1])
		module_line( md, &p );
		return;
	}
	
	
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
// 		printf("Drawing type %d\n", cur_e->type);
		
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
					
					polygon_drawShade(&temp, src, ds, lighting);
// 					printf("Drawing polygon at: ");
// 					polygon_print(&temp, stdout);
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

void module_cube( Module *md, int solid ) {

}
