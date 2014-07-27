#include <stdio.h>
#include <nano_bmp.h>
#include "vertex.h"
#include "microgl_driver.h"
#include "microgl.h"

int main(int argc, char **argv){
	microgl_driver_t *driver = microgl_driver_new(128, 128);
	microgl_driver_use(driver);

	mgl_begin(TRIANGLES);
	mgl_color(1, 0, 0);
	mgl_vertex3(0, 0, 0);
	mgl_color(0, 1, 0);
	mgl_vertex3(1, 0, 0);
	mgl_color(0, 0, 1);
	mgl_vertex3(1, 1, 0);
	mgl_end();

	bmp_t *bmp = create_bmp(driver->width, driver->height, 32);

	for (int x = 0; x < driver->width; ++x){
		for (int y = 0; y < driver->height; ++y){
			uint32_t p = driver->color_buffer[y * driver->width + x];
			set_pixel(bmp, x, driver->height - y, GET_RED(p), GET_BLUE(p), GET_GREEN(p));
		}
	}

	write_bmp("out.bmp", bmp);

	destroy_bmp(bmp);
	microgl_driver_destroy(driver);
	return 0;
}
