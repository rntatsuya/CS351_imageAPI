/**
 * Kimberly and Tatsuya
 * module.c
 */

////////////////////////////////////////
// General Module + Element Functions //
////////////////////////////////////////

Element *element_create() {

}

Element *element_init( ObjectType type, void *obj ) {

}

void element_delete( Element *e ) {

}

Module *module_create() {

}

void module_clear( Module *md ) {

}

void module_delete( Module *md ) {

}

void module_insert( Module *md, Element *e ) {

}

void module_module( Module *md, Module *sub ) {

}

void module_point( Module *md, Point *p ) {

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
