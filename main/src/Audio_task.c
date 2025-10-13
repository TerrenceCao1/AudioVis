#include "Audio_task.h"
#include "driver/i2s_common.h"
#include "driver/i2s_types.h"
#include "esp_err.h"
#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "hal/i2s_types.h"
#include "portmacro.h"
#include "string.h"
#include "freertos/queue.h"
#include "driver/i2s_std.h"

QueueHandle_t bufferQueue;
QueueHandle_t fftToLEDQueue;

int32_t samplingBuffer[BUFFER_SIZE];
float fftBuffer[BUFFER_SIZE];

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



void sampleAudioData(void * pvParameter)
{
    size_t bytes_read;
	i2s_init();

    while (1)
    {
		esp_err_t ret = i2s_channel_read(rx_handle, samplingBuffer, sizeof(samplingBuffer), &bytes_read, portMAX_DELAY);

		if (ret != ESP_OK)
		{
			printf("I2S read Error: %d, bytes: %u\n", ret, bytes_read);
			vTaskDelay(pdMS_TO_TICKS(10));
			while(1);
		}

		//INMP441 gives us 24 bit i2s, so we need to bitshift and typecast to float
		for(int i = 0; i < BUFFER_SIZE; i++)
		{
			int32_t s24 = samplingBuffer[i] >> 8;
			fftBuffer[i] = (float)s24 * 100/ 8388608.0f; //2^32 to normalize the float
		}
		
		if(xQueueSend(bufferQueue, &fftBuffer, portMAX_DELAY)){}

		vTaskDelay(pdMS_TO_TICKS(10));
    }
}

#define FFT_BANDS 32
#define MIN_BAND_VALUE 2
#define MAX_BAND_VALUE 32

SemaphoreHandle_t LEDBufferMutex;
float LED_Buffer[FFT_BANDS];

void xFFT(void* pvParameters)
{
    fft_config_t *fft_config = fft_init(BUFFER_SIZE, FFT_REAL, FFT_FORWARD, NULL, NULL);

	//creating borders for the FFT_Bins
	int bandBins[FFT_BANDS+1]; //number of bands + 1 for edges
	bandBins[0] = MIN_BAND_VALUE;
	for(int i = 1; i < FFT_BANDS+1; i++)
	{
		double ratio = (double)i/FFT_BANDS;
		double value = MIN_BAND_VALUE * pow((double)MAX_BAND_VALUE/MIN_BAND_VALUE, ratio);

		bandBins[i] = (int)round(value);

		if(bandBins[i] <= bandBins[i-1])
		{
			bandBins[i] = bandBins[i-1] + 1;
		}
	}

	float bandAmps[FFT_BANDS];
	while (1)
	{
		if (xQueueReceive(bufferQueue, &fftBuffer, portMAX_DELAY))
		{
			memcpy(fft_config->input, &fftBuffer, BUFFER_SIZE * sizeof(float));
			fft_execute(fft_config);

			for (int i = 0; i < FFT_BANDS; i++)
			{
				for(int j = bandBins[i]; j < bandBins[i+1]; j++)
				{
					bandAmps[i] += sqrtf(pow(fft_config->output[2*j], 2) + pow(fft_config->output[2*j + 1], 2));
				}
				bandAmps[i] /= (bandBins[i+1] - bandBins[i]);
			}

			if(xSemaphoreTake(LEDBufferMutex, portMAX_DELAY))
			{
				memcpy(LED_Buffer, bandAmps, sizeof(bandAmps));
				xSemaphoreGive(LEDBufferMutex);
			}

			memset(&bandAmps, 0, sizeof(bandAmps));
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
    taskYIELD();        
    fft_destroy(fft_config);
}
