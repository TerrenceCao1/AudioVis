#include "LED_task.h"
#include <soc/i2s_reg.h>

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

    i2s_driver_install(I2S_NUM_0, &i2s_cfg, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_cfg);

}