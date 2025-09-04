#include "Audio_task.h"
#include "driver/i2s.h"
#include "driver/i2s_common.h"
#include "freertos/projdefs.h"
#include "hal/i2s_types.h"
#include "portmacro.h"
#include "string.h"
#include "freertos/queue.h"
#include "math.h"
#include "fft.h"
#include "driver/i2s_std.h"

QueueHandle_t bufferQueue;

int32_t bufferA[BUFFER_SIZE];
int32_t bufferB[BUFFER_SIZE];

int32_t *samplingBuffer = bufferA;
int32_t *otherBuffer = bufferB;
float fftBuffer[BUFFER_SIZE];


void I2S_Init(i2s_chan_handle_t rx_handle, i2s_chan_config_t chan_cfg)
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

    while (1)
    {
		printf("sampling\n");
		//error check + populate buffer:
		esp_err_t ret = i2s_read(I2S_NUM_0, samplingBuffer, sizeof(int32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);

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
			fftBuffer[i] = (float)s24 / 8388608.0f; //2^32 to normalize the float
		}
		int32_t* temp = samplingBuffer;
		samplingBuffer = otherBuffer;
		otherBuffer = temp;
		
		if(xQueueSend(bufferQueue, &fftBuffer, portMAX_DELAY))
		{
			printf("sampling done\n");
		}

		vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void xFFT(void* pvParameters)
{
    fft_config_t *fft_config = fft_init(BUFFER_SIZE, FFT_REAL, FFT_FORWARD, NULL, NULL);

	int bandBins[FFT_BANDS+1]; //number of bands + 1 for edges
	for(int i = 0; i < FFT_BANDS+1; i++)
	{
		//exponentially sized bins since human hearing is logarithmic
		float f = pow(BUFFER_SIZE/2, (float)i/FFT_BANDS);
		bandBins[i] = (int)f;
		
		//make sure each frequency bin is actually different (low end is all the same)
		if(i > 0 && (bandBins[i] <=bandBins[i-1]))
		{
			bandBins[i] = bandBins[i-1] + 1;
		}
	}

	int bandAmps[FFT_BANDS];
	
		while (1)
		{
			if (xQueueReceive(bufferQueue, &fftBuffer, portMAX_DELAY))
			{
				printf("start of FFT\n");
				memcpy(fft_config->input, fftBuffer, sizeof(float) * BUFFER_SIZE);
				fft_execute(fft_config);
				
				//for each bin, we add up all the fft real values between those bounds.
				for (int i = 0; i < FFT_BANDS; i++)
				{
					for(int j = bandBins[i]; j < bandBins[i+1]; j++)
					{
						bandAmps[i] += sqrtf(pow((float)fft_config->output[2*j], 2) + pow((float)fft_config->output[2*j + 1], 2));
					}
					bandAmps[i] /= (bandBins[i+1] - bandBins[i]);
					printf("Bin %i Amp: %i\n", i, bandAmps[i]);
				}
			}
			vTaskDelay(pdMS_TO_TICKS(10));
		}
    taskYIELD();        
    fft_destroy(fft_config);
}
