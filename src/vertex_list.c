#include <stdlib.h>
#include "vertex.h"
#include "vertex_list.h"

vertex_list_t* vertex_list_new(){
	vertex_list_t *list = malloc(sizeof(vertex_list_t));
	if (list){
		list->head = NULL;
	}
	return list;
}
void vertex_list_destroy(vertex_list_t *list){
	if (!list){
		return;
	}
	vertex_list_clear(list);
	free(list);
}
void vertex_list_clear(vertex_list_t *list){
	if (!list){
		return;
	}
	vertex_node_t *cur = list->head;
	while (cur != NULL){
		vertex_node_t *next = cur->next;
		vertex_node_destroy(cur);
		cur = next;
	}
}
void vertex_node_destroy(vertex_node_t *node){
	if (node){
		free(node->vertex);
		free(node);
	}
}
void vertex_list_push(vertex_list_t *list, vertex_t vertex){
	vertex_node_t *node = malloc(sizeof(vertex_node_t));
	if (!node){
		return;
	}
	node->next = list->head;
	node->vertex = malloc(sizeof(vertex_t));
	node->vertex->pos = vertex.pos;
	node->vertex->color = vertex.color;
	list->head = node;
}
vertex_t* vertex_list_at(vertex_list_t *list, int i){
	vertex_node_t *node = list->head;
	for (int j = 0; j < i && node != NULL; ++j){
		node = node->next;
	}
	return node->vertex;
}

