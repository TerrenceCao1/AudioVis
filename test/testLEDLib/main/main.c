#include "esp_rom_sys.h"
#include "matrix_wrapper.h"

void app_main(void)
{
	matrix_init(64, 32);
	matrix_draw_pixel(10, 10, 0xFF00);
	matrix_draw_row(5, 0xFFF000F3F21F931F, 0xFFFF);
}
