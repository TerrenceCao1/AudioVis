#include "LED_task.h"
#include <soc/i2s_reg.h>
#include <driver/i2s.h>

void setup_i2s(void)
{
    i2s_config_t i2s_cfg = 
    {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX), //the microcontroller transmits led data through i2s to matrix
        .sample_rate = 1000000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_MSB),
        .dma_buf_count = 2,
        .dma_buf_len = WIDTH * 2,  // 16-bit samples
        .use_apll = false,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1
    };

    i2s_pin_config_t pin_cfg = 
    {
        .bck_io_num = -1,
        .ws_io_num = -1,
        .data_out_num = R1_PIN,
        .data_in_num = -1,
    };

    //i2s port 0 is being used for audio
    i2s_driver_install(I2S_NUM_1, &i2s_cfg, 0, NULL);
    i2s_set_pin(I2S_NUM_1, &pin_cfg);
}

void selectRow(int row)
{
    //check if the row is between 0 -> 31
    if (!(row >= 0 && row < HEIGHT))
    {
        printf("selected row is not in boundary.");
        while(1);
    }

    //set GPIOs based on the row...
        //for instance: row 5 = 0101, turn gpio's B and D on
    gpio_set_level(A_PIN, row >> 3 && 0b1);
    gpio_set_level(B_PIN, row >> 2 && 0b1);
    gpio_set_level(C_PIN, row >> 1 && 0b1);
    gpio_set_level(D_PIN, row && 0b1);
}