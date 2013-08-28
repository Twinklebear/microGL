#include <stdio.h>
#include "vector4f.h"
#include "matrix4f.h"

int main(int argc, char **argv){
	matrix4f_t mA = matrix4f_identity();
	printf("Matrix A\n");
	matrix4f_print(&mA);

	matrix4f_t mB = matrix4f_identity();
	mB.columns[3].x = 10;
	printf("Matrix B\n");
	matrix4f_print(&mB);

	matrix4f_t mC = matrix4f_new();
	matrix4f_mult(&mA, &mB, &mC);
	printf("Matrix C = A * B\n");
	matrix4f_print(&mC);

	vector4f_t vA = matrix4f_mult_vec(&mC, vector4f_new(1, 2, 3, 1));
	printf("Vector A = Matrix C * (1, 2, 3, 1)\n");
	vector4f_print(vA);

	vector4f_t vB = matrix4f_mult_vec(&mC, vector4f_new(1, 2, 3, 0));
	printf("Vector A = Matrix C * (1, 2, 3, 0)\n");
	vector4f_print(vB);

	return 0;
}