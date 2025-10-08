#include "LED_task.h"

void xDrawLEDLevels(void *pvParameter)
{
	float* floatLEDBuffer;
	int* intLEDBuffer;
	while(1)
	{
		if(xQueueReceive(fftToLEDQueue, &floatLEDBuffer, portMAX_DELAY))
		{
			for(int i = 0; i < FFT_BANDS; i++)
			{
				intLEDBuffer[i] = (int)floatLEDBuffer[i];
			}
			matrix_draw_audio_levels(intLEDBuffer);
		}
	}
}
