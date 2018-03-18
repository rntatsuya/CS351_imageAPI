#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

int main ( int argc, char *argv[] ) {

	Matrix m, b; 
    FILE *fp;

    matrix_clear( &m );

    // matrix_identity( &m );
    matrix_set( &m, 2, 1, 21.0);
    matrix_set( &m, 3, 0, 30.0);
    matrix_transpose(&m);

    matrix_print( &m, fp );

    if (fp != stdin)
        fclose(fp);


	return(0);
}