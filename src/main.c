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