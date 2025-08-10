#include "Audio_task.h"
#include "driver/i2s.h"
#include "freertos/queue.h"

//initing queue for buffer pointer
QueueHandle_t xBufferQueue = NULL;

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
    //buffer initialization
    int32_t *buffer = (int32_t *) pvParameter;
    size_t bytes_read;

    //creating freeRTOS queue -> send a pointer to the array
    xBufferQueue = xQueueCreate(5, sizeof(uint32_t*));
    if(xBufferQueue == NULL)
    {
        printf("Queue Creation Error what the heck");
    }

    while (1)
    {
        //populate buffer
        i2s_read(I2S_NUM_0, buffer, sizeof(uint32_t) * BUFFER_SIZE, &bytes_read, portMAX_DELAY);

        //put pointer to buffer in the queue
        xQueueSend(xBufferQueue, &buffer, 10);
        printf("pointer sent YUH *****\n");
    }
}

void xFFT(void* pvParameters)
{

    fft_config_t *fft_config = fft_init(512, FFT_REAL, FFT_FORWARD, NULL, NULL);
    
    while (1)
    {
        fft_execute(fft_config);

        //recieve the pointer to buffer from queue:
        int32_t* RxedPointers[5];
        if (xQueueReceive(xBufferQueue, &(RxedPointers), 10) == pdPASS)
        {
            
            for (int i = 0; i < BUFFER_SIZE; i++)
            {
                fft_config->input[i] = *(RxedPointers[0] + i);
            }

            printf("DC Component: %f\n", fft_config -> output[0]);
            for (int k = 1; k < fft_config -> size / 2; k++)
            {
                printf("%d-th frequency: %f+j%f\n", k, fft_config -> output[2*k], fft_config -> output[2*k + 1]);
            }
            printf("Middle Component: %f\n", fft_config -> output[1]);
        }

        fft_destroy(fft_config);
    }
}
