#include "driver/i2s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "LED_task.h"
#include "esp_log.h"
#include "driver/gpio.h"

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

#define CLK_PULSE gpio_set_level(CLK_PIN, 1); gpio_set_level(CLK_PIN, 0);

//trying to set Row 5, Column 10 pixel red
void app_main() {
    //init GPIO's
    gpio_config_t gpio_cfg = 
    {
        .pin_bit_mask = ((1ULL << R1_PIN) | (1ULL << G1_PIN) | (1ULL << B1_PIN) | (1ULL << R2_PIN) | (1ULL << G2_PIN) | (1ULL << B2_PIN) | (1ULL << CLK_PIN) | (1ULL << LAT_PIN) | (1ULL << OE_PIN) | (1ULL < A_PIN) |
         (1ULL << B_PIN) | (1ULL << C_PIN)| (1ULL << D_PIN)),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    }; 

    gpio_config(&gpio_cfg);

    gpio_set_level(OE_PIN, 1);
    gpio_set_level(CLK_PIN, 0);
    gpio_set_level(LAT_PIN, 0);

    //set row values: 10 = 1010 
    gpio_set_level(A_PIN, 1);
    gpio_set_level(C_PIN, 1);

    //set redFrameBuffer to be pixel 10
    uint64_t frameBuffer = 0;
    frameBuffer |= (0x1 << 10);

    //sending it to LED matrix
    for (int i = 0; i < WIDTH; i++)
    {
        gpio_set_level(R1_PIN, frameBuffer << i & 1);
        CLK_PULSE;
    }
    
    gpio_set_level(OE_PIN, 0);
    vTaskDelay(1 / portTICK_PERIOD_MS);
    gpio_set_level(OE_PIN, 1);
}