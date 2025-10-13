#include <matrix_wrapper.h>
#include "LED_task.h"
#include "Audio_task.h"
#include "freertos/idf_additions.h"

/*
    INMP441 PINOUT/WIRING:
    VDD: 3v2
    GND: GND
    SD: GPIO 33
    SCK: GPIO 32
    WS: GPIO 25
    L/R: GND

    LED ARRAY WIRING:
    RED0: GPIO 4
    RED1: GPIO 12
    GREEN0: GPIO 5
    GREEN1: GPIO 13
    BLUE0: GPIO 14
    BLUE1: GPIO 16
    A: GPIO 17
    B: GPIO 18
    C: GPIO 19
    D: GPIO 21
    CLK: GPIO 22
    LATCH: GPIO 23
    OE: GPIO 27
    GND: GND
*/

void app_main() {
	bufferQueue = xQueueCreate(1, sizeof(float*));
	fftToLEDQueue = xQueueCreate(1, sizeof(float*));
	LEDBufferMutex = xSemaphoreCreateMutex();


    xTaskCreatePinnedToCore(sampleAudioData, "SamplingI2S", 8192, NULL, 4, NULL, 0);
    xTaskCreatePinnedToCore(xFFT, "FFT", 8192, NULL, 4, NULL, 0);
	xTaskCreatePinnedToCore(xDrawLEDLevels, "DrawLEDLevels", 8192, NULL, 5, NULL, 1);
}
