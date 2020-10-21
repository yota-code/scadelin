#ifndef INCLUDE_scadelin_mat_H
#define INCLUDE_scadelin_mat_H

#include "scadelin_common.h"

int mat_mul(mat_T * input_a, mat_T * input_b, mat_T * output_c);
int mat_print(mat_T * a);

#endif /* INCLUDE_scadelin_mat_H */