#ifndef VERTEX_H
#define VERTEX_H

#include <stdint.h>
#include "vector4f.h"

/*
 * Describes a vertex by its color and position
 */
typedef struct vertex_t {
	vector4f_t pos, color;
} vertex_t;

/*
 * Create a vertex at some position and assign the RGB color
 * RGB values should be in the range [0-1]
 */
vertex_t vertex_new(vector4f_t pos, vector4f_t color);

#endif

