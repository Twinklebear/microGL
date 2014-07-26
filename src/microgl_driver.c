#include <stdlib.h>
#include "microgl.h"
#include "microgl_driver.h"

microgl_driver_t* microgl_driver_new(uint32_t width, uint32_t height){
	microgl_driver_t *driver = (microgl_driver_t*)malloc(sizeof(microgl_driver_t));
	if (!driver){
		return NULL;
	}
	driver->model_view.top = NULL;
	driver->projection.top = NULL;
	driver->stack_ptr = &driver->model_view;
	driver->vertex_list.head = NULL;
	driver->mode = TRIANGLES;
	driver->active_color = vector4f_new(0, 0, 0, 0);
	driver->width = width;
	driver->height = height;
	driver->color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * width * height);
	driver->depth_buffer = (float*)malloc(sizeof(float) * width * height);
	return driver;
}
void microgl_driver_destroy(microgl_driver_t *driver){
	if (!driver){
		return;
	}
	matrix4f_stack_clear(&driver->model_view);
	matrix4f_stack_clear(&driver->projection);
	vertex_list_clear(&driver->vertex_list);
	free(driver->color_buffer);
	free(driver->depth_buffer);
	free(driver);
}
void microgl_driver_use(microgl_driver_t *driver){
	extern microgl_driver_t *mgl_active_driver;
	mgl_active_driver = driver;
}



