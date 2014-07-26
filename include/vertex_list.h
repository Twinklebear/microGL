#ifndef VERTEX_LIST_H
#define VERTEX_LIST_H

#include <stdlib.h>
#include "vertex.h"

/*
 * An expandable array of vertices, behaves like a C++ std::vector
 */
typedef struct vertex_list_t {
	size_t size, capacity;
	vertex_t *vertices;
} vertex_list_t;
/*
 * Create the vertex list with some initial capacity
 */
vertex_list_t vertex_list_new(size_t capacity);
/*
 * Destroy the list
 */
void vertex_list_destroy(vertex_list_t *list);
/*
 * Push a copy of the vertex onto the end of the list
 */
void vertex_list_push_back(vertex_list_t *list, vertex_t vertex);

#endif

