/*
  Bruce A. Maxwell
  Fall 2014

	Skeleton scanline fill algorithm
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graphics.h"
#include "list.h"

/********************
Scanline Fill Algorithm
********************/

// define the struct here, because it is local to only this file
typedef struct tEdge {
	float x0, y0, z0, x1, y1, z1;       /* start/end points for the edge */
	int yStart, yEnd;               	/* start row and end row */
	float xIntersect, dxPerScan, zIntersect, dzPerScan;    
	struct tEdge *next;
} Edge;


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the yStart field of the
	Edge structure.  It is used to sort the overall edge list.
 */
static int compYStart( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	return(ea->yStart - eb->yStart);
}


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the xIntersect field of the
	Edge structure.  It is used to sort the active edge list.
 */
static int compXIntersect( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	if( ea->xIntersect < eb->xIntersect )
		return(-1);
	else if(ea->xIntersect > eb->xIntersect )
		return(1);

	return(0);
}

/*
	Allocates, creates, fills out, and returns an Edge structure given
	the inputs.

	Current inputs are just the start and end location in image space.
	Eventually, the points will be 3D and we'll add color and texture
	coordinates.
 */
static Edge *makeEdgeRec( Point start, Point end, Image *src)
{
	// Allocate an edge structure and set the x0, y0, x1, y1 values
	Edge *edge = malloc( sizeof(Edge) );
	edge->x0 = start.val[0];
	edge->y0 = start.val[1];
	edge->z0 = start.val[2];

	edge->x1 = end.val[0];
	edge->y1 = end.val[1];
	edge->z1 = end.val[2];

	// Check if the starting row is below the image or the end row is
	// above the image and skip the edge if either is true
	if ( edge->y0 > src->rows || edge->y1 < 0 )  // Checks bounds of y values 
		return NULL;

	// Turn on an edge only if the edge starts in the top half of it or
	// the lower half of the pixel above it.  In other words, round the
	// start y value to the nearest integer and assign it to
	// edge->yStart.
	edge->yStart = (int)(start.val[1] + 0.5);

	// Turn off the edge if it starts in the lower half or the top half
	// of the next pixel.  In other words, round the end y value to the
	// nearest integer and subtract 1, assigning the result to
	// edge->yEnd.
	edge->yEnd = (int)(end.val[1] + 0.5) - 1;

	// Clip yEnd to the number of rows-1.
	if ( edge->yEnd >= src->rows )
		edge->yEnd = src->rows - 1; 

	// Calculate the slope, dxPerScan for z and x
	float dscan = end.val[1] - start.val[1]; 
	edge->dxPerScan = (end.val[0] - start.val[0]) / dscan;
	edge->dzPerScan = (1/end.val[2] - 1/start.val[2]) / dscan;

	// Calculate xIntersect, adjusting for the fraction of the point in the pixel.
	// Scanlines go through the middle of pixels
	// Move the edge to the first scanline it crosses
	if (edge->y1 - (int)edge->y1 >= 0.5) {
		edge->xIntersect = edge->x0 + (edge->yStart + 0.5 - edge->y0) * edge->dxPerScan;
		edge->zIntersect = 1/edge->z0 + (edge->yStart + 0.5 - edge->y0) * edge->dzPerScan;
	} else {
		edge->xIntersect = edge->x0 + (edge->yStart + 1.5 - edge->y0) * edge->dxPerScan;
		edge->zIntersect = 1/edge->z0 + (edge->yStart + 1.5 - edge->y0) * edge->dzPerScan;
	}
	
	// Move the intersections down to scanline zero
	if ( edge->y0 < 0 ) {
		// Returns x to a safe value if out-of-bounds 
	    edge->xIntersect += -edge->yStart * edge->dxPerScan;
	    edge->zIntersect += -edge->yStart * edge->dzPerScan;
	    edge->yStart = 0;

	    // Sets up x0 and y0
	    edge->x0 = ( edge->y1 - edge->y0 ) / ( edge->dxPerScan + edge->x0 );
	    edge->z0 = ( edge->y1 - edge->y0 ) / ( edge->dzPerScan + edge->z0 );
	    edge->y0 = edge->y0 + ( -1 * edge->y0 );
	}

	// Check for really bad cases with steep slopes where xIntersect has gone beyond the end of the edge
    if ( ((edge->xIntersect) > (edge->x1)) && (edge->dxPerScan > 0) ) {
		edge->xIntersect = edge->x1 - 1;
		edge->zIntersect = edge->z1 - 1;
    } if ( ((edge->xIntersect) < (edge->x1)) && (edge->dxPerScan < 0) ) {
    	edge->xIntersect = edge->x1 - 1;
    	edge->zIntersect = edge->z1 - 1;
    }

	// return the newly created edge data structure
	return(edge);
}


/*
	Returns a list of all the edges in the polygon in sorted order by
	smallest row.
*/
static LinkedList *setupEdgeList( Polygon *p, Image *src, DrawState *ds ) {
	LinkedList *edges = NULL;
	Point v1, v2;
	int i;

	// create a linked list
	edges = ll_new();

	// walk around the polygon, starting with the last point
	v1 = p->vertex[p->nVertex-1];

	for(i=0;i<p->nVertex;i++) {
		
		// the current point (i) is the end of the segment
		v2 = p->vertex[i];

		// if it is not a horizontal line
		if( (int)(v1.val[1]+0.5) != (int)(v2.val[1]+0.5) ) {
			Edge *edge;

			// if the first coordinate is smaller (top edge)
			if( v1.val[1] < v2.val[1] )
				edge = makeEdgeRec( v1, v2, src );
			else
				edge = makeEdgeRec( v2, v1, src );

			// insert the edge into the list of edges if it's not null
			if( edge )
				ll_insert( edges, edge, compYStart );
		}
		v1 = v2;
	}

	// check for empty edges (like nothing in the viewport)
	if( ll_empty( edges ) ) {
		ll_delete( edges, NULL );
		edges = NULL;
	}

	return(edges);
}

/*
	Draw one scanline of a polygon given the scanline, the active edges,
	a DrawState, the image, and some Lights (for Phong shading only).
 */
static void fillScan( int scan, LinkedList *active, Image *src, DrawState *ds ) {
  Edge *p1, *p2;

	// loop over the list
  p1 = ll_head( active );
  while(p1) {
		// the edges have to come in pairs, draw from one to the next
	  p2 = ll_next( active );
	  if( !p2 ) {
		  printf("bad bad bad (your edges are not coming in pairs)\n");
		  break;
	  }

		// if the xIntersect values are the same, don't draw anything.
		// Just go to the next pair.
		if( p2->xIntersect == p1->xIntersect ) {
			p1 = ll_next( active );
			continue;
		}

		float dzPerColumn = (p2->zIntersect - p1->zIntersect)/(p2->xIntersect-p1->xIntersect);
		float curZ = 1/p1->zIntersect;

		// Identify the starting column
		// clip to the left side of the image
		int start = p1->xIntersect;
		if ( start < 0 ) {
			curZ += dzPerColumn*(-start);
			start = 0;
		}

		// Identify the ending column
		// clip to the right side of the image
		int end = p2->xIntersect;
		if ( end >= src->cols )
			end = src->cols - 1;

		// float z = 1/curZ;
		// Loop from start to end and color in the pixels
	  	for ( int i = start ; i < end; i++ ) {
	  		printf("curZ:%.5f z-buff:%.5f\n",curZ, image_getz(src, scan, i) );

	  		if ( curZ > image_getz(src, scan, i) ) {
	  			if (ds->shade == ShadeConstant) {
		  			image_setColorFunc( src, scan, i, ds->color );
	  			} else if (ds->shade == ShadeDepth) {
		  			image_fillrgb( src, 
		  				curZ*ds->color.c[0], 
		  				curZ*ds->color.c[1], 
		  				curZ*ds->color.c[2] );
		  		}
		  		curZ += dzPerColumn;
		  	}
	  	}
		// Move ahead to the next pair of edges
	  	p1 = ll_next( active );
  }

	return;
}

/*
	Draw one scanline of a polygon given the scanline, the active edges,
	a DrawState, the image, and some Lights (for Phong shading only).
 */
static void fillScanGradient( int scan, LinkedList *active, Image *src, Color c1, Color c2, Point a, Point b ) {
  Edge *p1, *p2;
  // int i, f;

	// loop over the list
  p1 = ll_head( active );
  while(p1) {
		// the edges have to come in pairs, draw from one to the next
	  p2 = ll_next( active );
	  if( !p2 ) {
		  printf("bad bad bad (your edges are not coming in pairs)\n");
		  break;
	  }

		// if the xIntersect values are the same, don't draw anything.
		// Just go to the next pair.
	  if( p2->xIntersect == p1->xIntersect ) {
		  p1 = ll_next( active );
		  continue;
	  }

		// Identify the starting column
		// clip to the left side of the image
		int start = p1->xIntersect;
		if ( start < 0 ) 
			start = 0;

		// Identify the ending column
		// clip to the right side of the image
		int end = p2->xIntersect;
		if ( end >= src->cols )
			end = src->cols - 1;
	  
	    printf("Point a: %f, %f\nPoint b: %f, %f\n", a.val[0], a.val[1], b.val[0], b.val[1]);
		// Loop from start to end and color in the pixels
	  	for ( int i = start ; i < end; i++ ) 
	  		image_setColorGradient( src, a.val[0], a.val[1], b.val[0], b.val[1], scan, i, c1, c2 );

		// Move ahead to the next pair of edges
	  	p1 = ll_next( active );
  }

	return;
}

/* 
	 Process the edge list, assumes the edges list has at least one entry
*/
static int processEdgeList( LinkedList *edges, Image *src, DrawState *ds ) {
	LinkedList *active = NULL;
	LinkedList *tmplist = NULL;
	LinkedList *transfer = NULL;
	Edge *current;
	Edge *tedge;
	int scan = 0;

	active = ll_new( );
	tmplist = ll_new( );

	// get a pointer to the first item on the list and reset the current pointer
	current = ll_head( edges );

	// start at the first scanline and go until the active list is empty
	for ( scan = current->yStart;scan < src->rows;scan++ ) {

		// grab all edges starting on this row
		while( current != NULL && current->yStart == scan ) {
			ll_insert( active, current, compXIntersect );
			current = ll_next( edges );
		}
		// current is either null, or the first edge to be handled on some future scanline

		if( ll_empty(active) ) {
			break;
		}

		// if there are active edges
		// fill out the scanline
		fillScan( scan, active, src, ds );

		// remove any ending edges and update the rest
		for( tedge = ll_pop( active ); tedge != NULL; tedge = ll_pop( active ) ) {

			// keep anything that's not ending
			if( tedge->yEnd > scan ) {
				float a = 1.0;

				// update the edge information with the dPerScan values
				tedge->xIntersect += tedge->dxPerScan;
				tedge->zIntersect += tedge->dzPerScan;

				// adjust in the case of partial overlap
				if( tedge->dxPerScan < 0.0 && tedge->xIntersect < tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
					tedge->zIntersect = tedge->z1;
				}
				else if( tedge->dxPerScan > 0.0 && tedge->xIntersect > tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
					tedge->zIntersect = tedge->z1;
				}

				ll_insert( tmplist, tedge, compXIntersect );
			}
		}

		transfer = active;
		active = tmplist;
		tmplist = transfer;

	}

	// get rid of the lists, but not the edge records
	ll_delete(active, NULL);
	ll_delete(tmplist, NULL);

	return(0);
}

/* 
	 Process the edge list, assumes the edges list has at least one entry
*/
static int processEdgeListGradient( LinkedList *edges, Image *src, Color c1, Color c2, Point a, Point b ) {
	LinkedList *active = NULL;
	LinkedList *tmplist = NULL;
	LinkedList *transfer = NULL;
	Edge *current;
	Edge *tedge;
	int scan = 0;

	active = ll_new( );
	tmplist = ll_new( );

	// get a pointer to the first item on the list and reset the current pointer
	current = ll_head( edges );

	// start at the first scanline and go until the active list is empty
	for(scan = current->yStart;scan < src->rows;scan++ ) {

		// grab all edges starting on this row
		while( current != NULL && current->yStart == scan ) {
			ll_insert( active, current, compXIntersect );
			current = ll_next( edges );
		}
		// current is either null, or the first edge to be handled on some future scanline

		if( ll_empty(active) ) {
			break;
		}

		// if there are active edges
		// fill out the scanline
		fillScanGradient( scan, active, src, c1, c2, a, b);

		// remove any ending edges and update the rest
		for( tedge = ll_pop( active ); tedge != NULL; tedge = ll_pop( active ) ) {

			// keep anything that's not ending
			if( tedge->yEnd > scan ) {
				float a = 1.0;

				// update the edge information with the dPerScan values
				tedge->xIntersect += tedge->dxPerScan;

				// adjust in the case of partial overlap
				if( tedge->dxPerScan < 0.0 && tedge->xIntersect < tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
				}
				else if( tedge->dxPerScan > 0.0 && tedge->xIntersect > tedge->x1 ) {
					a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
				}

				ll_insert( tmplist, tedge, compXIntersect );
			}
		}

		transfer = active;
		active = tmplist;
		tmplist = transfer;

	}

	// get rid of the lists, but not the edge records
	ll_delete(active, NULL);
	ll_delete(tmplist, NULL);

	return(0);
}

/*
	Draws a filled polygon of the specified color into the image src.
 */
void polygon_drawState(Polygon *p, Image *src, DrawState *ds ) {
	LinkedList *edges = NULL;

	// set up the edge list
	edges = setupEdgeList( p, src, ds );
	if( !edges )
		return;
	
	// process the edge list (should be able to take an arbitrary edge list)
	processEdgeList( edges, src, ds );

	// clean up
	ll_delete( edges, (void (*)(const void *))free );

	return;
}

/*
	Draws a filled polygon of the specified color into the image src.
 */
// void polygon_drawFill(Polygon *p, Image *src, Color c ) {
// 	LinkedList *edges = NULL;

// 	// set up the edge list
// 	edges = setupEdgeList( p, src );
// 	if( !edges )
// 		return;
	
// 	// process the edge list (should be able to take an arbitrary edge list)
// 	processEdgeList( edges, src, c);

// 	// clean up
// 	ll_delete( edges, (void (*)(const void *))free );

// 	return;
// }

// void polygon_drawFillGradient(Polygon *p, Image *src, Color c1, Color c2, Point a, Point b ) {
// 	LinkedList *edges = NULL;

// 	// set up the edge list
// 	edges = setupEdgeList( p, src );
// 	if( !edges )
// 		return;
	
// 	// process the edge list (should be able to take an arbitrary edge list)
// 	processEdgeListGradient( edges, src, c1, c2, a, b);

// 	// clean up
// 	ll_delete( edges, (void (*)(const void *))free );

// 	return;
// }

/****************************************
End Scanline Fill
*****************************************/
