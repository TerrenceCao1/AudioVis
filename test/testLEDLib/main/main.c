#include "esp_rom_sys.h"
#include "matrix_wrapper.h"

void app_main(void)
{
	int levels[WIDTH/2];
	for(int i = 0; i < WIDTH/2; i++)
	{
		levels[i] = i;
	}
	matrix_init(WIDTH, HEIGHT);

	matrix_draw_pixel(5, 10, 0xF000);

	/*
	while(1)
	{
		for(int i = 0; i < HEIGHT; i++)
		{
			matrix_draw_row(i, 0xFF88FF88FF88FF88, 0xFFFF);
			esp_rom_delay_us(100000);
		}
		matrix_clear();
		esp_rom_delay_us(1000000);
	}*/
}
