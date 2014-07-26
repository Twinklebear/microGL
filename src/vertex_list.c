#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "vertex_list.h"

vertex_list_t vertex_list_new(size_t capacity){
	vertex_list_t list;
	list.size = 0;
	list.capacity = capacity;
	list.vertices = (vertex_t*)malloc(sizeof(vertex_t) * capacity);
	return list;
}
void vertex_list_destroy(vertex_list_t *list){
	free(list->vertices);
	list->size = 0;
	list->capacity = 0;
}
void vertex_list_push_back(vertex_list_t *list, vertex_t vertex){
	if (list->size + 1 == list->capacity){
		vertex_list_expand(list, 2 * list->capacity);
	}
	list->vertices[list->size] = vertex;
	list->size++;
}
void vertex_list_expand(vertex_list_t *list, size_t capacity){
	vertex_t *vertices = list->vertices;
	list->vertices = (vertex_t*)malloc(sizeof(vertex_t) * capacity);
	memcpy(list->vertices, vertices, sizeof(vertex_t) * list->size);
	list->capacity = capacity;
	free(vertices);
}

