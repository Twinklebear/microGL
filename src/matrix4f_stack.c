#include <stdlib.h>
#include "matrix4f.h"
#include "matrix4f_stack.h"

matrix4f_node_t* matrix4f_node_new(matrix4f_t mat){
	matrix4f_node_t *node = malloc(sizeof(matrix4f_node_t));
	node->matrix = mat;
	node->next = NULL;
	return node;
}

matrix4f_stack_t* matrix4f_stack_new(){
	matrix4f_stack_t *stack = malloc(sizeof(matrix4f_stack_t));
	stack->top = NULL;
	return stack;
}
void matrix4f_stack_destroy(matrix4f_stack_t *stack){
	if (stack->top != NULL){
		matrix4f_node_t *cur, *next;
		for (cur = stack->top; cur != NULL; cur = next){
			next = cur->next;
			free(cur);
		}
	}
	free(stack);
}
void matrix4f_stack_push(matrix4f_stack_t *stack, matrix4f_t mat){
	matrix4f_node_t *node = matrix4f_node_new(mat);
	node->next = stack->top;
	stack->top = node;
}
matrix4f_t matrix4f_stack_pop(matrix4f_stack_t *stack){
	if (stack->top == NULL){
		return matrix4f_new();
	}
	matrix4f_node_t *node = stack->top;
	stack->top = stack->top->next;
	matrix4f_t mat = node->matrix;
	free(node);
	return mat;
}
int matrix4f_stack_empty(const matrix4f_stack_t *stack){
	return stack->top == NULL;
}
