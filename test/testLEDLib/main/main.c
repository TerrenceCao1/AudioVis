#include "esp_rom_sys.h"
#include "freertos/projdefs.h"
#include "matrix_wrapper.h"
#include "stdio.h"
#include "freertos/FreeRTOS.h"

float levels[WIDTH];
float levels_rev[WIDTH];

void app_main(void)
{
	matrix_init(WIDTH, HEIGHT);	
	int i = 0;
	while(i < WIDTH)
	{
		levels[i] = (float)i;
		i++;
	}

	i = 0;
	while(i < WIDTH)
	{
		levels_rev[i] = (float)(31-i);
		i++;
	}

	while(1)
	{
		matrix_draw_audio_levels(levels_rev);
		esp_rom_delay_us(100000);
		matrix_clear();
		matrix_draw_audio_levels(levels);
		esp_rom_delay_us(100000);
		matrix_clear();
	}
}
