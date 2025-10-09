#include "driver/i2s_common.h"
#include "driver/i2s_std.h"
#include "driver/i2s_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include <math.h>
#include <fft.h>

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
    function: I2S_Init -> initialize i2s_config and i2s_pin_config and install i2s driver
    input: void
    output: void
*/
void i2s_init(void);

/*
    function: sampleAudioData -> samples I2S audio data from IMNP441 microphone
    input: buffer array to be filled with data
    output: buffer gets filled with audio data
*/
void sampleAudioData(void *pvParameter);

/*
    function: fastFourierTransform -> takes buffer array and performs a fast fourier transform
    input: pointer to buffer containing audio data
    output: void
*/
void xFFT(void *pvParameter);

#endif //AUDIO_TASK_h_
