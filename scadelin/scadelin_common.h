#ifndef INCLUDE_scadelin_common_H
#define INCLUDE_scadelin_common_H

#include <stdlib.h>

typedef struct {
	size_t row;
	size_t col;
	float * data;
} mat_T;

// the data already exists
#define NEW_mat_T(name, val_p, row_n, col_n) \
	static mat_T name = {0}; \
	name.row = row_n; \
	name.col = col_n; \
	name.data = val_p;

#define MAT(m, i, j) ( (m)->data[(i*(m)->col) + j] )

#endif