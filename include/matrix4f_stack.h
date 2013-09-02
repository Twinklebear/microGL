#ifndef MATRIX4F_STACK_H
#define MATRIX4F_STACK_H

#include "matrix4f.h"

/*
* A node in the matrix stack
*/
typedef struct matrix4f_node_t {
	matrix4f_t matrix;
	struct matrix4f_node_t *next;
} matrix4f_node_t;
/*
* Create a new node and pass a matrix to be used
*/
matrix4f_node_t* matrix4f_node_new(matrix4f_t mat);

/*
* A matrix stack implemented as a single linked list
*/
typedef struct matrix4f_stack_t {
	matrix4f_node_t *top;
} matrix4f_stack_t;
/*
* Create a new matrix stack
*/
matrix4f_stack_t* matrix4f_stack_new();
/*
* Destroy the matrix stack
*/
void matrix4f_stack_destroy(matrix4f_stack_t *stack);
/*
* Push a matrix onto the top of the stack
*/
void matrix4f_stack_push(matrix4f_stack_t *stack, matrix4f_t mat);
/*
* Pop the top matrix off the stack and return it
* if pop is called on an empty stack a blank matrix is returned
*/
matrix4f_t matrix4f_stack_pop(matrix4f_stack_t *stack);
/*
* Check if the stack is empty, will return 1 if empty
*/
int matrix4f_stack_empty(const matrix4f_stack_t *stack);

#endif
