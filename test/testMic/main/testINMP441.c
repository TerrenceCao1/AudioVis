#include "driver/i2s_common.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"

#define I2S_PORT  I2S_NUM_0

#define I2S_WS    25
#define I2S_SCK   32
#define I2S_SD    33

i2s_chan_handle_t rx_handle;
i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_PORT, I2S_ROLE_MASTER);

void i2s_init(void)
{
    ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, NULL, &rx_handle));

    i2s_std_config_t std_cfg = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(44100),
        .slot_cfg = {
            .data_bit_width = I2S_DATA_BIT_WIDTH_32BIT,
            .slot_bit_width = I2S_SLOT_BIT_WIDTH_32BIT,
            .slot_mode      = I2S_SLOT_MODE_MONO,
			.slot_mask      = I2S_STD_SLOT_LEFT,
            .ws_width       = I2S_DATA_BIT_WIDTH_32BIT,
            .ws_pol         = false,
            .bit_shift      = true,
            .msb_right      = false,
        },
        .gpio_cfg = {
            .mclk       = I2S_GPIO_UNUSED,
            .bclk       = I2S_SCK,
            .ws         = I2S_WS,
            .dout       = I2S_GPIO_UNUSED,
            .din        = I2S_SD,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv   = false,
            },
        },
    };

    ESP_ERROR_CHECK(i2s_channel_init_std_mode(rx_handle, &std_cfg));

    ESP_ERROR_CHECK(i2s_channel_enable(rx_handle));
}

int app_main(void)
{
	i2s_init();
	int32_t buffer[128];
	size_t bytes_read = 0;

	while(1)
	{
		i2s_channel_read(rx_handle, buffer, sizeof(buffer), &bytes_read, 1000);

		for(int i = 0; i < 128; i++)
		{
			float out = (buffer[i] >> 8) * 100/8388608.0f;
			printf("%i, %f\n", i, out);
			//printf("%f ", out);
		}
		printf("\n\n");
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	return 0;
}
