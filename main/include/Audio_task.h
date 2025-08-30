//headers for audio - taking samples from INMP and performing FFT
#include "driver/i2s.h"
#include "freertos/queue.h"
#include <math.h>
#include <fft.h>

#ifndef AUDIO_TASK_h_
#define AUDIO_TASK_h_

//setting the pins
#define I2S_SCLK GPIO_NUM_32
#define I2S_WS GPIO_NUM_25
#define I2S_SD GPIO_NUM_33
#define I2S_PORT I2S_NUM_0
#define BUFFER_SIZE 512

extern SemaphoreHandle_t xBufferReadySem;
extern float bufferA[BUFFER_SIZE];
extern float bufferB[BUFFER_SIZE];
extern float *samplingBuffer;
extern float *fftBuffer;

/*
    functions needed:
        I2S_Init
        Sample_I2S_Audio
        FFT_Audio_Sample
*/

/*
    function: I2S_Init -> initialize i2s_config and i2s_pin_config and install i2s driver
    input: void
    output: void
*/
void I2S_Init(i2s_config_t *mainConfig, i2s_pin_config_t *pinConfig);

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
