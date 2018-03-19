#ifndef VIEW_H

#define VIEW_H

typedef struct {
	Point v0; 	// The center of the view rectangle V0 in world coordinates
	double du; 	// The width of the view rectangle du in world coordinates
	double theta; 	// The orientation angle v_theta or the x-axis of the view window expressed as a normalized vector (nx, ny).
				// The relationship between the two is given by (nx, ny) = (cos(✓v),sin(✓v)).
	int c; 		// The number of columns C in the output image
	int r; 		// The number of rows R in the output image
} View2D;


typedef struct {
	Point vrp;		// 3-D vector indicating origin of view ref coords
	Vector vpn;		// 3-D vector indicating dir in which viewer is looking
	Vector vup;		// 3-D vector indicating up direction on view plane 	
	double d;		// Distance in the -VPN dir where center of proj located
	double du;		// du/dv: extent of view plane around the VRP, 
	double dv;		// in world coordinate distances
	double f;		// front and back clip planes expressed as distances along 
	double b;		// the positive VPN. F > 0 and F <B.
	int screenx;	// Size of desired image in pixels
	int screeny;
} View3D;

// Sets vtm to be the view transformation defined by the 2DView structure.
void matrix_setView2D(Matrix *vtm, View2D *view);

// Implements the 3D perspective pipeline
void matrix_setView3D( Matrix *vtm, View3D *view );

#endif VIEW_H