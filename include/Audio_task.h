//headers for audio - taking samples from INMP and performing FFT
#ifndef AUDIO_TASK_h_
#define AUDIO_TASK_h_

//setting the pins
#define I2S_SCLK GPIO_NUM_14
#define I2S_WS GPIO_NUM_25
#define I2S_SD GPIO_NUM_32
#define I2S_PORT I2S_NUM_0

/*
    functions needed:
        I2S_Init
        Sample_I2S_Audio
        FFT_Audio_Sample
*/

/*
    function: I2S_Init -> initialize i2s_config and i2s_pin_config and install i2s driver
    input: void
    output: void
*/
void I2S_Init(mainConfig, pinConfig);



#endif //AUDIO_TASK_h_