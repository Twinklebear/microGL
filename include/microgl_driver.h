#ifndef MICROGL_DRIVER_H
#define MICROGL_DRIVER_H

#include <stdint.h>
#include "matrix4f_stack.h"
#include "vertex_list.h"

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

