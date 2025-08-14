//header for driving LED Matrix
#include <math.h>
#include <driver/i2s.h>
#include <soc/i2s_reg.h>


#ifndef LED_TASK_h_
#define LED_TASK_h_


//pin definitions:
#define R0_PIN GPIO_NUM_4
#define G0_PIN GPIO_NUM_5
#define B0_PIN GPIO_NUM_14
#define R1_PIN GPIO_NUM_12
#define G1_PIN GPIO_NUM_13
#define B1_PIN GPIO_NUM_16
#define CLK_PIN GPIO_NUM_22
#define LAT_PIN GPIO_NUM_23
#define OE_PIN GPIO_NUM_27
#define A_PIN GPIO_NUM_17
#define B_PIN GPIO_NUM_18
#define C_PIN GPIO_NUM_19
#define D_PIN GPIO_NUM_21

//LED Matrix Dimensions
#define WIDTH 64
#define HEIGHT 32

typedef struct 
{
    uint16_t* frameBuffer;
    uint8_t brightness;
} led_matrix_data_t;


/*
    function: setup_i2s - set i2s and pin configuration and link i2s config to GPIO's
    input: void
    output: void
*/
void setup_i2s(void);

/*
    function: selectRow - set the A, B, C, D pins based on the row we are trying to obtain
    input: int row
    output: void (but the A B C D gpios will be set)
*/
void selectRow(int row);


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