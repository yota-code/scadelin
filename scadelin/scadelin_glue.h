#ifndef INCLUDE_scadelin_glue_H
#define INCLUDE_scadelin_glue_H

#include "scadelin_mat.h"

#define INIT_mat_T(name, val_p, row_n, col_n) \
	static mat_T name = {0}; \
	name.row = row_n; \
	name.col = col_n; \
	name.data = val_p;

void mat_mul__scade__(float * input_a, float * input_b, float * output_c, size_t row_a, size_t col_a, size_t col_b);
void mat_print__scade__(void * input_a, size_t row_a, size_t col_a);

#endif