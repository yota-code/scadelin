#ifndef INCLUDE_scadelin_common_H
#define INCLUDE_scadelin_common_H

#include <stdlib.h>

typedef struct {
	size_t row;
	size_t col;
	float * p;
} mat_T;

// the data already exists somewhere, we just want to link to it
#define MAT__init__(name, data, row_n, col_n) \
	mat_T name = {0}; \
	name.row = row_n; \
	name.col = col_n; \
	name.p = data;

// the data is created localy (very convenient sometimes) 
#define MAT__new__(name, row_n, col_n) \
	float name##_data[row_n * col_n]; \
	mat_T name = {0}; \
	name.row = row_n; \
	name.col = col_n; \
	name.p = name##_data;

// #define MAT(m, i, j) ( ( (m)->p == 0 ) ? ( (m)->p[(i*(m)->col) + j] ) : ( (m)->p[(i*(m)->col) + j] ) )

#define MAT(m, i, j) ( (m)->p[(i*(m)->col) + j] )


#define MAT__assert__(m, i, j) assert( 0 <= i && i < ((m)->row) && 0 <= j && j < ((m)->col) )

#endif