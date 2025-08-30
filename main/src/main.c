#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "Audio_task.h"
#include "LED_task.h"
#include "esp_log.h"


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
	//setup for the i2s
    static i2s_config_t i2s_config;
    static i2s_pin_config_t i2s_pin_config;
    I2S_Init(&i2s_config, &i2s_pin_config);
    xBufferReadySem = xSemaphoreCreateBinary();

    xTaskCreatePinnedToCore(sampleAudioData, "SamplingI2S", 8192, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(xFFT, "fft", 8192, NULL, 4, NULL, 1);
}
