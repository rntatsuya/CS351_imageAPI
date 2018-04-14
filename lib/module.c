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
	e->obj = (Object)NULL; // dunno if casting nulls makes any sense...
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
				// Not sure how to implement
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
	printf("adding element type %d\n", e->type );
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
	// void *p = &sub;
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
	printf("\nMODULE DRAW\n");
	Matrix LTM;
	matrix_identity( &LTM );
	
	Element *cur_e = md->head;
	
	while ( cur_e ) { // Break when pointer reaches end of LL
		printf("Handling type %d\n", cur_e->type);
		switch( cur_e->type ) {
			case ObjColor:
				{
// 					printf("color\n");
					ds->color = cur_e->obj.color;
					break;
				}

			case ObjPoint:
				{
// 					printf("point\n");
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
// 					printf("line\n");
					Line temp;
					line_copy( &temp, &(cur_e->obj.line) );
					matrix_xformLine( &LTM, &temp );
					matrix_xformLine( GTM, &temp );
					matrix_xformLine( VTM, &temp );
					line_normalize( &temp );
					line_draw( &temp, src, ds->color );
					line_print( &temp, stdout );
					break;
				}

			case ObjPolygon:
				{
// 					printf("polygon\n");
					Polygon temp;
					polygon_copy( &temp, &(cur_e->obj.polygon) );
					matrix_xformPolygon( &LTM, &temp );
					matrix_xformPolygon( GTM, &temp );
					matrix_xformPolygon( VTM, &temp );
					polygon_normalize( &temp );
					
					polygon_drawShade(&temp, src, ds, lighting);
					printf("Drawing polygon at: ");
					polygon_print(&temp, stdout);
					break;
				}

			case ObjMatrix:
				{
// 					printf("matrix\n");
					matrix_multiply( &(cur_e->obj.matrix), &LTM, &LTM ); 
					break;
				}

			case ObjIdentity:
				{
// 					printf("identity\n");
					matrix_identity( &LTM );
					break;
				}

			case ObjModule:
				{
// 					printf("module\n");
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
//		printf("moving pointer to next element\n");
		cur_e = cur_e->next; 
	}
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
