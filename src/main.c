#include <stdio.h>
#include "microgl.h"
#include "microgl_driver.h"

int main(int argc, char **argv){

	microgl_driver_t *driver = microgl_driver_new(640, 480);
	microgl_driver_use(driver);
	microgl_driver_destroy(driver);

	return 0;
}
