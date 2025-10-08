#include "LED_task.h"
#include "freertos/projdefs.h"
#include "matrix_wrapper.h"

void xDrawLEDLevels(void *pvParameter)
{
	float floatLEDBuffer[WIDTH/2];
	while(1)
	{
		matrix_draw_pixel(5, 5, 0xFFFF);
		if(xQueueReceive(fftToLEDQueue, &floatLEDBuffer, portMAX_DELAY))
		{
			matrix_draw_audio_levels(floatLEDBuffer);
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}
