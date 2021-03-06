#include <stdio.h>
#include <assert.h>

#include "config_types.h"

#include "scadelin_mat.h"

/*
	it is not possible to have a convenient function which return a variable sized data
	the only way is to pass a pointer as an argument !
	If a pointer is returned, the memory associated being de-allocated at the exit, it is useless
*/

int mat_mul(mat_T * a, mat_T * b, mat_T * c) {
	/**
		c = a * b, where a, b, c are matrices
	**/

	// check the coherency for the matrices size
	assert( a->col == b->row && a->row == c->row && b->col == c->col );

	for (size_t i=0 ; i < a->row ; i++) {
		for (size_t j=0 ; j < b->col ; j++) {
			MAT__assert__(c, i, j);
			MAT(c, i, j) = 0;
			for (size_t k=0 ; k < a->row ; k++){
					MAT__assert__(a, i, k);
					MAT__assert__(b, k, j);
					MAT(c, i, j) += MAT(a, i, k) * MAT(b, k, j);
			}
		}
	}

}

int mat_print(mat_T * a) {
	/**
		print the content of the matrix a to stdout
	**/
	for (size_t i=0 ; i < a->row ; i++) {
		for (size_t j=0 ; j < a->col ; j++) {
			printf("%f ", MAT(a, i, j));
		}
		printf("\n");
	}
}

