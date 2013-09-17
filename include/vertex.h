#ifndef VERTEX_H
#define VERTEX_H

#include <stdint.h>
#include "vector4f.h"

//Color masks for working with vertex colors
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00

#define SET_RED(P, C)	(P = ((P & ~RMASK) | (C << 24)))
#define SET_GREEN(P, C)	(P = ((P & ~GMASK) | (C << 16)))
#define SET_BLUE(P, C)	(P = ((P & ~BMASK) | (C << 8)))
#define GET_RED(P)   ((P & RMASK) >> 24)
#define GET_GREEN(P) ((P & GMASK) >> 16)
#define GET_BLUE(P)  ((P & BMASK) >> 8)

/*
 * Describes a vertex by its color and position
 */
typedef struct vertex_t {
	vector4f_t pos;
	uint32_t color;
} vertex_t;

/*
 * Create a vertex at some position and assign the RGB color
 * RGB values should be in the range [0-1]
 */
vertex_t vertex_new(vector4f_t pos, vector4f_t color);

#endif

