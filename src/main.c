#include <stdio.h>
#include "vertex.h"
#include "vertex_list.h"

int main(int argc, char **argv){
	vertex_list_t list = vertex_list_new(2);
	vertex_list_push_back(&list, vertex_new(vector4f_new(0, 0, 1, 0), vector4f_new(1, 0, 0, 1)));
	vertex_list_push_back(&list, vertex_new(vector4f_new(1, 0, 1, 0), vector4f_new(1, 1, 0, 1)));
	vertex_list_push_back(&list, vertex_new(vector4f_new(0, 1, 1, 0), vector4f_new(1, 1, 1, 1)));

	for (int i = 0; i < list.size; ++i){
		vector4f_t pos = list.vertices[i].pos;
		printf("vertex at %d pos = [%f, %f, %f, %f]\n",
			i, pos.x, pos.y, pos.z, pos.w);
	}
	vertex_list_destroy(&list);

	return 0;
}
