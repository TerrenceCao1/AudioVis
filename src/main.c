#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "Audio_task.h"
#include "LED_task.h"

void app_main() {
    //setup for the i2s

    static const i2s_config_t i2s_config;
    static const i2s_pin_config_t i2s_pin_config;
    I2S_Init(i2s_config, i2s_pin_config);
    
    //RTOS TASKS:
        //FFT - HIGHEST priority
        //Driving LEDs - 2nd highest
        //ADC/Microphone Sampling - 3rd
}