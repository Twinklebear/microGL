#ifndef VERTEX_LIST_H
#define VERTEX_LIST_H

#include "vertex.h"

/*
 * A simple single-linked list of vertices. I suppose I could
 * do things more generically with void*'s and such but for such
 * simple applications, meh.
 */
typedef struct vertex_node_t {
	vertex_t *vertex;
	struct vertex_node_t *next;
} vertex_node_t;

typedef struct vertex_list_t {
	vertex_node_t *head;
} vertex_list_t;
/*
 * Create the vertex list
 */
vertex_list_t* vertex_list_new();
/*
 * Destroy the list
 */
void vertex_list_destroy(vertex_list_t *list);
/*
 * Destroy all nodes in the list
 */
void vertex_list_clear(vertex_list_t *list);
/*
 * Destroy a list node
 */
void vertex_node_destroy(vertex_node_t *node);
/*
 * Push a copy of the vertex onto the front of the list
 */
void vertex_list_push(vertex_list_t *list, vertex_t vertex);
/*
 * Get the element at some index in the list of vertices
 */
vertex_t* vertex_list_at(vertex_list_t *list, int i);

#endif

