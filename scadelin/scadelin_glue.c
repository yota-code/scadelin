#include <stdio.h>

#include "scadelin_common.h"
#include "scadelin_glue.h"

void mat_mul__scade__(float * data_a, float * data_b, float * data_c, size_t row_a, size_t col_a, size_t col_b) {
	NEW_mat_T(a, data_a, row_a, col_a);
	NEW_mat_T(b, data_b, col_a, col_b);
	NEW_mat_T(c, data_c, row_a, col_b);

	printf("mat_mul__scade__()\ta[0][0] = %f\n", MAT(&a, 0, 0));

	mat_mul(&a, &b, &c);
}

void mat_print__scade__(float * data_a, size_t row_a, size_t col_a) {
	NEW_mat_T(a, data_a, row_a, col_a);

	mat_print(&a);
}
