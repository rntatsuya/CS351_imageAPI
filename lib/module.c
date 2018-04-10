/**
 * Kimberly and Tatsuya
 * module.c
 */

////////////////////////////////////////
// General Module + Element Functions //
////////////////////////////////////////

Element *element_create() {
	Element *e = malloc(sizeof(Element));
	
	if (!e) {
    	printf("Ran out of memory while mallocing Element pointer in element_create!\n");
    	exit(-1);
	}
	
// 	e->type = NULL;
// 	e->obj = NULL;
// 	e->next = NULL;
	
	return e;
}

Element *element_init( ObjectType type, void *obj ) {
	Element *e = element_create();
	// make copy of original obj
	Object copyObj;
	
	switch(type) {
		case Point :
// 			copyObj.point. = obj;
			point_copy(&copyObj.point, &obj);
			break;
		case Line :
// 			copyObj.line = obj->line;
			line_copy(&copyObj.line, &obj);
			break;
		case Polyline :
// 			copyObj.polyline = obj->polyline;
			polyline_copy(&copyObj.polyline, &obj);
			break;
		case Polygon :
// 			copyObj.polygon = obj->polygon;
			polygon_copy(&copyObj.polygon, &obj)
			break;
		case Matrix :
//			copyObj.matrix = obj->matrix;
			matrix_copy( &copyObj.matrix, &obj );
			break;
		case Color :
//			obj.color = obj->color;
			copyObj.color.c[0] = obj->c[0];
			copyObj.color.c[1] = obj->c[1];
			copyObj.color.c[2] = obj->c[2];
			break;
		case float :
			copyObj.coeff = *obj;
			break;
		case void* : // module case
			copyObj.module = obj;
			break;
	}
	
	e->type = type;
	e->obj = copyObj;
	
	return e;
}

void element_delete( Element *e ) {
	switch(e->type) {
		case Point :

			break;
		case Line :
			
			break;
		case Polyline :

			break;
		case Polygon :

			break;
		case Matrix :

			break;
		case Color :

			break;
		case float :

			break;
		case void* : // module case

			break;
	}
}

Module *module_create() {
	Module *md = malloc(sizeof(Module));
	
	md->head = NULL;
	md->tail = NULL;
	
	return md;
}

void module_clear( Module *md ) {
	Element *cur_e = md->head;
	Element *temp
	
	// loop till we get a NULL for the next pointer
	while (cur_e->next) {
		temp = cur_e;
		
		
		cur_e = temp->next;
	}
}

void module_delete( Module *md ) {

}

void module_insert( Module *md, Element *e ) {
	if (!md->head) {
		md->head = e;
		md->tail = e;
		return;
	}
	Element *cur_e = md->head;
	
	// loop till we get a NULL for the next pointer
	while (cur_e->next) {
		cur_e = cur_e->next;
	}
	
	cur_e->next = e;
	md->tail = e;
}

void module_module( Module *md, Module *sub ) {
	Element *e;
	void *p = &sub;
	e = element_init( ObjModule, p );

	module_insert( md, e );
}

void module_point( Module *md, Point *p ) {
	Element *e;
	e = element_init( ObjLine, p );

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
	e = element_init( ObjPolygon, p );

	module_insert( md, e );
}

void module_identity( Module *md ) {
	Element *e;
	Matrix *m;

	matrix_identity( m );
	e = element_init( ObjIdentity, m );

	module_insert( md, e );
}

void module_color(Module *md, Color *c) { 

}


/////////////////////////
// 2D Module Functions //
/////////////////////////

void module_translate2D( Module *md, double tx, double ty ) {
	Element *e;
	Matrix *m;

	matrix_translate2D( m, tx, ty );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_scale2D( Module *md, double sx, double sy ) {
	Element *e;
	Matrix *m;

	matrix_scale2D( m, sx, sy );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void matrix_rotateZ( Module *md, double cth, double sth ) {
	Element *e;
	Matrix *m;

	matrix_scale2D( m, cth, sth );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_shear2D( Module *md, double shx, double shy ) {
	Element *e;
	Matrix *m;

	matrix_shear2D( m, shx, shy );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_draw( Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src ) {
	
}


/////////////////////////
// 3D Module Functions //
/////////////////////////

void module_translate( Module *md, double tx, double ty, double tz ) {
	Element *e;
	Matrix *m;

	matrix_translate( m, tx, ty, tz );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_scale( Module *md, double sx, double sy, double sz ) {
	Element *e;
	Matrix *m;

	matrix_scale( m, sx, sy, sz );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_rotateX( Module *md, double cth, double sth ) {
	Element *e;
	Matrix *m;

	matrix_rotateX( m, cth, sth );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_rotateY( Module *md, double cth, double sth ) {
	Element *e;
	Matrix *m;

	matrix_rotateY( m, cth, sth );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_rotateXYZ( Module *md, Vector *u, Vector *v, Vector *w ) {
	Element *e;
	Matrix *m;

	matrix_rotateXYZ( m, u, v, w );
	e = element_init( ObjMatrix, m );

	module_insert( md, e );
}

void module_cube( Module *md, int solid ) {

}
