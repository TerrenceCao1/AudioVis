#include "driver/i2s_common.h"
#include "driver/i2s_std.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <math.h>
#include <FFT.h>

#ifndef AUDIO_TASK_h_
#define AUDIO_TASK_h_

#define I2S_SCK GPIO_NUM_32
#define I2S_WS GPIO_NUM_25
#define I2S_SD GPIO_NUM_33
#define I2S_PORT I2S_NUM_0
#define BUFFER_SIZE 512
#define FFT_BANDS 32

extern QueueHandle_t bufferQueue;
extern QueueHandle_t fftToLEDQueue;
extern int32_t samplingBuffer[BUFFER_SIZE];
extern float fftBuffer[BUFFER_SIZE];

extern SemaphoreHandle_t LEDBufferMutex;
extern float LED_Buffer[FFT_BANDS];

/*
 * @brief	Initiates I2S communication between esp32 microcontroller and INMP441 Microphone
 *
 *			Configures settings compatible with INMP441, sets pinout, and creates I2S Channel
*/
void i2s_init(void);

/*
 * @brief	Obtains raw I2S Audio Data from INMP441 and formats it for FFT function
 *
 *			This function reads I2S from INMP441, stores it into a samplingBuffer, copies it over and normalizes each data point as a float, and sends a pointer to the new buffer over a Queue.
 *
*/
void sampleAudioData(void *pvParameter);

/*
 * @brief	Performs Fast Fourier Transform on I2S data to obtain frequency and amplitude data
 *
 *			This function creates frequency bins (chunking a 512pt FFT into 32 bins for later use), recieves a pointer to the raw audio data, performs the FFT and sums the frequencies in each bin. 
* */
void xFFT(void *pvParameter);

#endif //AUDIO_TASK_h_
