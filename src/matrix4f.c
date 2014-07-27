#include <stdio.h>
#include "vector4f.h"
#include "matrix4f.h"

matrix4f_t matrix4f_new(){
	matrix4f_t m;
	for (int i = 0; i < 4; ++i){
		m.columns[i].x = 0;
		m.columns[i].y = 0;
		m.columns[i].z = 0;
		m.columns[i].w = 0;
	}
	return m;
}
matrix4f_t matrix4f_identity(){
	matrix4f_t m;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			if (i == j){
				vector4f_set_idx(&m.columns[i], j, 1);
			}
			else {
				vector4f_set_idx(&m.columns[i], j, 0);
			}
		}
	}
	return m;
}
void matrix4f_set_col(matrix4f_t *m, int c, float x, float y, float z, float w){
	m->columns[c].x = x;
	m->columns[c].y = y;
	m->columns[c].z = z;
	m->columns[c].w = w;
}
vector4f_t matrix4f_get_row(const matrix4f_t *m, int r){
	vector4f_t row;
	for (int i = 0; i < 4; ++i){
		vector4f_set_idx(&row, i, vector4f_get_idx(m->columns[i], r));
	}
	return row;
}
vector4f_t matrix4f_mult_vec(const matrix4f_t *m, vector4f_t v){
	vector4f_t res;
	for (int i = 0; i < 4; ++i){
		vector4f_set_idx(&res, i, vector4f_dot(matrix4f_get_row(m, i), v));
	}
	return res;
}
void matrix4f_mult(const matrix4f_t *a, const matrix4f_t *b, matrix4f_t *c){
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			vector4f_set_idx(&c->columns[j], i,
				vector4f_dot(matrix4f_get_row(a, i), b->columns[j]));
		}
	}
}
void matrix4f_print(const matrix4f_t *m){
	printf("Matrix, row by row:\n--------\n");
	for (int i = 0; i < 4; ++i){
		vector4f_print(matrix4f_get_row(m, i));
	}
	printf("--------\n");
}
