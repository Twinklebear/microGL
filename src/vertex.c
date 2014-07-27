#include <math.h>
#include <stdint.h>
#include "vector4f.h"
#include "vertex.h"

vertex_t vertex_new(vector4f_t pos, vector4f_t color){
	vertex_t vertex;
	vertex.pos = pos;
	vertex.color = color;
	return vertex;
}

