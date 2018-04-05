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

}

void module_polyline( Module *md, Polyline *p ) {

}

void module_polygon( Module *md, Polygon *p ) {

}

void module_identity( Module *md ) {

}

// void module_color(Module *md, Color *c) { }


/////////////////////////
// 2D Module Functions //
/////////////////////////

void module_translate2D( Module *md, double tx, double ty ) {

}

void module_scale2D( Module *md, double sx, double sy ) {

}

void module_rotateZ( Module *md, double cth, double sth ) {

}

void module_shear2D( Module *md, double shx, double shy ) {

}

void module_draw( Module *md, Matrix *VTM, Matrix *GTM, DrawState *ds, Lighting *lighting, Image *src ) {

}


/////////////////////////
// 3D Module Functions //
/////////////////////////

void module_translate( Module *md, double tx, double ty, double tz ) {

}

void module_scale( Module *md, double sx, double sy, double sz ) {

}

void module_rotateX( Module *md, double cth, double sth ) {

}

void module_rotateY( Module *md, double cth, double sth ) {

}

void module_rotateXYZ( Module *md, Vector *u, Vector *v, Vector *w ) {

}

void module_cube( Module *md, int solid ) {

}
