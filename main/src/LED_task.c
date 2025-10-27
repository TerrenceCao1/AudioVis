#include "LED_task.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "matrix_wrapper.h"
#include "portmacro.h"

// TODO: Color changing Button!
void xDrawLEDLevels(void *pvParameter)
{
	matrix_init(WIDTH, HEIGHT);
	while(1)
	{
		if(xSemaphoreTake(LEDBufferMutex, portMAX_DELAY))
		{
			matrix_clear();
			matrix_draw_audio_levels(LED_Buffer, 0xFFFF);

			xSemaphoreGive(LEDBufferMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void xPrintLEDBuffer(void *pvParameter)
{
	float floatLEDBuffer[WIDTH/2];
	matrix_init(WIDTH, HEIGHT);
	while(1)
	{
		if(xQueueReceive(fftToLEDQueue, &floatLEDBuffer, portMAX_DELAY)) 
		{
			for(int i = 0; i < WIDTH/2; i++)
			{
				printf("floatLEDBuffer[%i]: %f\n", i, floatLEDBuffer[i]);
			}
			vTaskDelay(pdTICKS_TO_MS(10));
		}
	}
}
