#ifndef MATRIX4F_H
#define MATRIX4F_H

#include "vector4f.h"

/*
* A 4x4 matrix of floats, is stored as 4 vector4f's
* which represent the columns of the matrix
*/
typedef struct matrix4f_t {
	vector4f_t columns[4];
} matrix4f_t;

/*
* Create a blank matrix4f
*/
matrix4f_t matrix4f_new();
/*
* Create the identity matrix
*/
matrix4f_t matrix4f_identity();
/*
* Set the column of the matrix to some value
*/
void matrix4f_set_col(matrix4f_t *m, int c, float x, float y, float z, float w);
/*
* Get a row of the matrix
* Since the matrix is column order but we sometimes like to access rows
* easily as well this function is handy
*/
vector4f_t matrix4f_get_row(const matrix4f_t *m, int r);
/*
* Multiply a matrix with a vector
*/
vector4f_t matrix4f_mult_vec(const matrix4f_t *m, vector4f_t v);
/*
* Multiply two matrices together, the result will be stored in matrix c
*/
void matrix4f_mult(const matrix4f_t *a, const matrix4f_t *b, matrix4f_t *c);
/*
* Print a matrix out
*/
void matrix4f_print(const matrix4f_t *m);


#endif
