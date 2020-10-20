#ifndef _INCLUDE_SCADE_TYPES
	#include "scade_types.h"
#endif

#include "matmul_test.h"

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

	_C_matmul_test _C_ = {0};

	_C_._I0_a_3x5 = & a_3x5;
	_C_._I2_b_5x3 = & b_5x3;

	matmul_test(& _C_);



}