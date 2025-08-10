//header for driving LED Matrix
#include <math.h>
#include <driver/i2s.h>
#include <soc/i2s_reg.h>


#ifndef LED_TASK_h_
#define LED_TASK_h_


//pin definitions:
#define R1_PIN GPIO_NUM_12
#define G1_PIN GPIO_NUM_13
#define B1_PIN GPIO_NUM_14
#define R2_PIN GPIO_NUM_15
#define G2_PIN GPIO_NUM_16
#define B2_PIN GPIO_NUM_17
#define CLK_PIN GPIO_NUM_18
#define LAT_PIN GPIO_NUM_19
#define OE_PIN GPIO_NUM_21
#define A_PIN GPIO_NUM_22
#define B_PIN GPIO_NUM_23
#define C_PIN GPIO_NUM_25
#define D_PIN GPIO_NUM_26

//LED Matrix Dimensions
#define WIDTH 64
#define HEIGHT 32

//uint16_t* frameBuffer[2];
//volatile bool back_buffer = 0;

/*
    function: setup_i2s - set i2s and pin configuration and link i2s config to GPIO's
    input: void
    output: void
*/
void setup_i2s(void);

/*
    We must:
        Initialize LED Matrix
        Be able to write to specific registers (Row select) and R1, R2, G1, G2, B1, B2
        Write pixels to screen
        Write bars to the screen based on FFT buffer
*/

/*
    function: LED_init
    input: led_matrix_config_t matrixConfig
    
*/

#endif //LED_TASK_h_