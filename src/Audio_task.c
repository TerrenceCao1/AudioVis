#include "Audio_task.h"
#include "driver/i2s.h"
#include "freertos/queue.h"

void I2S_Init(i2s_config_t *mainConfig, i2s_pin_config_t *pinConfig)
{
    *mainConfig = (i2s_config_t){
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), //for microphone, we want our microcontroller to recieve
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_CHAN_24BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 1024,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    *pinConfig = (i2s_pin_config_t){
        .bck_io_num = I2S_SCLK,
        .ws_io_num = I2S_WS,
        .data_in_num = I2S_SD,
        .data_out_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_PORT, mainConfig, 0, NULL);
    i2s_set_pin(I2S_PORT, pinConfig);
}