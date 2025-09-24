#include "matrix_wrapper.h"

int app_main(void)
{
	matrix_init(64, 32);
	matrix_draw_pixel(10, 10, 0xFF00);
	return 1;
}
