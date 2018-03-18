#ifndef VIEW_H

#define VIEW_H

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

void matrix setView3D( Matrix *vtm, View3D *view );

#endif VIEW_H