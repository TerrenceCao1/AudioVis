#include "esp_rom_sys.h"
#include "matrix_wrapper.h"
#include "stdio.h"

int levels[WIDTH];

void app_main(void)
{
	matrix_init(WIDTH, HEIGHT);	
	int i = 0;
	while(i < WIDTH)
	{
		levels[i] = i;
		i++;
	}

	while(1)
	{
		matrix_draw_audio_levels(levels);
	}
}
