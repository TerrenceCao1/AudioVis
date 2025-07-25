#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "Audio_task.h"
#include "LED_task.h"
#include "esp_log.h"

#define BUFFER_SIZE 32 //this is the FFT length 

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
    
    uint32_t buffer[BUFFER_SIZE];
    while(1)
    {
        size_t bytes_read = 0;
        i2s_read(I2S_NUM_0, buffer, sizeof(uint32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);

        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%li, ", buffer[i]);
        }
    }
    
    //RTOS TASKS:
        //ADC/Microphone Sampling - Highest
        //FFT - 2nd Priority
        //Driving LEDs - 3rd
}