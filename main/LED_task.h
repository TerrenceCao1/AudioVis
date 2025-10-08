#include "freertos/idf_additions.h"
#include <math.h>
#include <driver/i2s.h>
#include <soc/i2s_reg.h>
#include "Audio_task.h"
#include "matrix_wrapper.h"
#include "freertos/queue.h"
#include "portmacro.h"

#ifndef LED_TASK_h_
#define LED_TASK_h_

extern QueueHandle_t fftToLEDQueue;

/*
	function: xDrawLEDLevels -> take in the fft data and draw it onto the LED matrix
	input: pointer to buffer containing audio data
	output: void
 *
 * */
void xDrawLEDLevels(void *pvParameter);

void xPrintLEDBuffer(void *pvParameter);
#endif //LED_TASK_h_
