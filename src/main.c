#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "Audio_task.h"
#include "LED_task.h"
#include "esp_log.h"
#include "fft.h"


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
    
    //buffer for i2s data
    int32_t buffer[BUFFER_SIZE];
    size_t bytes_read;

    //fft configuration structure
    while(1)
    {
        i2s_read(I2S_NUM_0, buffer, sizeof(uint32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);

        // Create the FFT config structure
        fft_config_t *real_fft_plan = fft_init(512, FFT_REAL, FFT_FORWARD, NULL, NULL);

        // Fill array with some data
        for (int k = 0; k < sizeof(buffer)/sizeof(uint32_t); k++)
        {
            real_fft_plan->input[k] = buffer[k];
        }

        // Execute transformation
        fft_execute(real_fft_plan);

        // Now do something with the output
        printf("DC component : %f\n", real_fft_plan->output[0]);  // DC is at [0]
        for (int k = 1 ; k < real_fft_plan->size / 2 ; k++)
        printf("%d-th freq : %f+j%f\n", k, real_fft_plan->output[2*k], real_fft_plan->output[2*k+1]);
        printf("Middle component : %f\n", real_fft_plan->output[1]);  // N/2 is real and stored at [1]

        // Don't forget to clean up at the end to free all the memory that was allocated
        fft_destroy(real_fft_plan);
    }
    
}