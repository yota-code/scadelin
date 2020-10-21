#ifndef INCLUDE_scadelin_glue_H
#define INCLUDE_scadelin_glue_H

#include "scadelin_mat.h"

void mat_mul__scade__(float * input_a, float * input_b, float * output_c, size_t row_a, size_t col_a, size_t col_b);
void mat_print__scade__(float * input_a, size_t row_a, size_t col_a);

#endif