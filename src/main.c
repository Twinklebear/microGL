#include <stdio.h>
#include "matrix4f.h"
#include "matrix4f_stack.h"

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
	printf("Matrix C\n");
	mC.columns[3].y = -5;
	matrix4f_print(&mC);

	matrix4f_stack_t *stack = matrix4f_stack_new();

	printf("Stack empty? %d\n", matrix4f_stack_empty(stack));

	matrix4f_stack_push(stack, mA);
	matrix4f_stack_push(stack, mB);
	matrix4f_stack_push(stack, mC);

	matrix4f_t top = matrix4f_stack_pop(stack);
	printf("1st pop expecting matrix C, matrix is:\n");
	matrix4f_print(&top);

	top = matrix4f_stack_pop(stack);
	printf("2nd pop expecting matrix B, matrix is:\n");
	matrix4f_print(&top);

	printf("Stack empty? %d\n", matrix4f_stack_empty(stack));

	top = matrix4f_stack_pop(stack);
	printf("final pop expecting matrix A, matrix is:\n");
	matrix4f_print(&top);	

	matrix4f_stack_destroy(stack);

	return 0;
}
