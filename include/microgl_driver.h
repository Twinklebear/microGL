#ifndef MICROGL_DRIVER_H
#define MICROGL_DRIVER_H

#include <stdint.h>
#include "matrix4f_stack.h"
#include "vertex_list.h"
#include "microgl.h"

//Color masks for the color buffer
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00

#define SET_RED(P, C) (P = ((P & ~RMASK) | (C << 24)))
#define SET_GREEN(P, C) (P = ((P & ~GMASK) | (C << 16)))
#define SET_BLUE(P, C) (P = ((P & ~BMASK) | (C << 8)))
#define GET_RED(P) ((P & RMASK) >> 24)
#define GET_GREEN(P) ((P & GMASK) >> 16)
#define GET_BLUE(P) ((P & BMASK) >> 8)

/*
 * The internal render driver
 */
typedef struct microgl_driver_t {
	matrix4f_stack_t model_view, projection;
	vertex_list_t vertex_list;
	//The pointer to the active stack
	matrix4f_stack_t *stack_ptr;
	poly_mode mode;
	vector4f_t active_color;
	uint32_t width, height;
	uint32_t *color_buffer;
	float *depth_buffer;
} microgl_driver_t;

/*
 * Initialize the driver to render to a target that is width X height
 */
microgl_driver_t* microgl_driver_new(uint32_t width, uint32_t height);
/*
 * Destroy the driver
 */
void microgl_driver_destroy(microgl_driver_t *driver);
/*
 * Set the active driver to be targetted for rendering
 */
void microgl_driver_use(microgl_driver_t *driver);

#endif

