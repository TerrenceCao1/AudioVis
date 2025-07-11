#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "Audio_task.h"
#include "LED_task.h"

void app_main() {
    //setup for the i2s
    I2S_Init();
    
    //RTOS TASKS:
        //FFT - HIGHEST priority
        //Driving LEDs - 2nd highest
        //ADC/Microphone Sampling - 3rd
}