#include "Audio_task.h"
#include "driver/i2s.h"
#include "portmacro.h"
#include "string.h"
#include "freertos/queue.h"
#include "math.h"
#include "fft.h"

QueueHandle_t bufferQueue;

float bufferA[BUFFER_SIZE];
float bufferB[BUFFER_SIZE];

float *samplingBuffer = bufferA;
float *fftBuffer = bufferB;

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

void sampleAudioData(void * pvParameter)
{
    size_t bytes_read;

    while (1)
    {
		printf("sampling\n");
		//error check + populate buffer:
		esp_err_t ret = i2s_read(I2S_NUM_0, samplingBuffer, sizeof(uint32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);

		if (ret != ESP_OK || bytes_read != sizeof(float) * BUFFER_SIZE)
		{
			printf("I2S read Error: %d, bytes: %d\n", ret, bytes_read);
			vTaskDelay(pdMS_TO_TICKS(10));
			continue;
		}

		//copy the sampling buffer over to the fftBuffer through temp
		float *temp = fftBuffer;
		fftBuffer = samplingBuffer;
		samplingBuffer = temp;
		
		xQueueSend(bufferQueue, &fftBuffer, portMAX_DELAY);
		printf("sampling done\n");
		vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void xFFT(void* pvParameters)
{
    fft_config_t *fft_config = fft_init(512, FFT_REAL, FFT_FORWARD, NULL, NULL);

	int bandBins[FFT_BANDS+1]; //number of bands + 1 for edges
	for(int i = 0; i < FFT_BANDS+1; i++)
	{
		//exponentially sized bins since human hearing is logarithmic
		float f = pow(256, (float)i/FFT_BANDS);
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
						bandAmps[i] += (int)fft_config->output[2*j];
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
