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
 * @brief	Takes data from FFT function and displays onto the LED Matrix
 *
 *			This function waits for the FFT function to finish populating a buffer of LED Levels based on amplitude of specific frequency bins
 *
 * @return	void
*/
void xDrawLEDLevels(void *pvParameter);

#endif //LED_TASK_h_
