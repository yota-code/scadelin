#include <stdio.h>
#include <assert.h>

#include "config_types.h"

#include "scadelin_mat.h"

int mat_mul(mat_T * a, mat_T * b, mat_T * c) {
	/**
		c = a * b, where a, b, c are matrices
	**/
	// check the coherency for the matrices size
	assert( a->col == b->row && a->row == c->row && b->col == c->col );
	for (size_t i=0 ; i < a->row ; i++) {
		for (size_t j=0 ; j < b->col ; j++) {
			MAT(c, i, j) = 0;
			for (size_t k=0 ; k < a->row ; k++){
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

