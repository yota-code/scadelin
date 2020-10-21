#include <stdio.h>

#ifndef _INCLUDE_SCADE_TYPES
	#include "scade_types.h"
#endif

#include "matmul_test.h"

#include "scadelin_glue.h"

mat_3x5 a_3x5 = {
	{1, 2, 3, 4, 5},
	{2, 3, 4, 5, 6},
	{3, 4, 5, 6, 7}
};

mat_5x3 b_5x3 = {
	{1, 2, 3},
	{2, 3, 4},
	{3, 4, 5},
	{4, 5, 6},
	{5, 6, 7}
};

int main() {

	_C_matmul_test matmul_test_C = {0};

	matmul_test_C._I0_a_3x5 = & a_3x5;
	matmul_test_C._I2_b_5x3 = & b_5x3;

	printf("main()\ta[0][0] = %f\n", matmul_test_C._I0_a_3x5->_F0._F0);
	printf("main()\ta[3][5] = %f\n", matmul_test_C._I0_a_3x5->_F2._F4);

	/*printf("matmul_test_C._I0_a_3x5 = %p\n", matmul_test_C._I0_a_3x5);
	printf("matmul_test_C._I2_b_5x3 = %p\n", matmul_test_C._I2_b_5x3);
	printf("& (matmul_test_C._O0_c_3x3) = %p\n", & (matmul_test_C._O0_c_3x3));
	
	mat_mul__scade__(
		(float *) matmul_test_C._I0_a_3x5,
		(float *) matmul_test_C._I2_b_5x3,
		(float *) & (matmul_test_C._O0_c_3x3),
		3, 5, 3
	);*/

	matmul_test(& matmul_test_C);

	mat_print__scade__((float *) & matmul_test_C._O0_c_3x3, 3, 3);

}