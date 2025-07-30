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
*/

void app_main() {
    //setup for the i2s

    static i2s_config_t i2s_config;
    static i2s_pin_config_t i2s_pin_config;
    I2S_Init(&i2s_config, &i2s_pin_config);
    
    int32_t buffer[BUFFER_SIZE];

    xTaskCreate(sampleAudioData, "SamplingI2S", 8192, (void *) buffer, configMAX_PRIORITIES - 1, NULL);
    
    //RTOS TASKS:
        //ADC/Microphone Sampling - Highest
        //FFT - 2nd Priority
        //Driving LEDs - 3rd
}