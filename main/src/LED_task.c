#include "LED_task.h"
#include "fft.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "matrix_wrapper.h"
#include "portmacro.h"

void xDrawLEDLevels(void *pvParameter)
{
	matrix_init(WIDTH, HEIGHT);
	while(1)
	{
		if(xSemaphoreTake(LEDBufferMutex, portMAX_DELAY))
		{
			printf("Mutex Taken by LED Task");
			matrix_clear();
			matrix_draw_audio_levels(LED_Buffer);

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
