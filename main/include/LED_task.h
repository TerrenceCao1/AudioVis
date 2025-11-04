#ifndef LED_TASK_h_
#define LED_TASK_h_

#include "freertos/idf_additions.h"
#include <math.h>
#include <driver/i2s.h>
#include <soc/i2s_reg.h>
#include "Audio_task.h"
#include "matrix_wrapper.h"
#include "freertos/queue.h"
#include "portmacro.h"
#include "driver/gpio.h"


#define BUTTON_PIN 35

extern QueueHandle_t fftToLEDQueue;
extern QueueHandle_t interputQueue;

/*
 * @brief	Takes data from FFT function and displays onto the LED Matrix
 *
 *			This function waits for the FFT function to finish populating a buffer of LED Levels based on amplitude of specific frequency bins
 *
 * @return	void
*/
void xDrawLEDLevels(void *pvParameter);


/*
 * @brief	Initiate GPIOS for interrupt
 *
 *			Sets BUTTON_PIN as an input that can take an interrupt
 *
 * @return	void
 *
 * */
void setInterruptGPIOs(void);

/*
 * @brief	Takes button press interrupt and updates counter such that LED Color changes
 *
 *			This function takes from interputQueue and updates a counter in order to cycle through a color array
 *
 *	@return void
 * */
void vColorChange(void* params);



#endif //LED_TASK_h_
