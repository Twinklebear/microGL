#include <math.h>
#include <stdint.h>
#include "vector4f.h"
#include "vertex.h"

vertex_t vertex_new(vector4f_t pos, vector4f_t color){
	vertex_t vertex;
	vertex.pos = pos;
	uint8_t r = (uint8_t)(fmax(fmin(color.x, 1.f), 0.f) * 255);
	uint8_t b = (uint8_t)(fmax(fmin(color.y, 1.f), 0.f) * 255);
	uint8_t g = (uint8_t)(fmax(fmin(color.z, 1.f), 0.f) * 255);
	SET_RED(vertex.color, r);
	SET_GREEN(vertex.color, g);
	SET_BLUE(vertex.color, b);

	return vertex;
}

