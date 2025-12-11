#ifndef MATRIX_WRAPPER_H
#define MATRIX_WRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#define NEW_PINOUT //switch with OLD_PINOUT for testing

#ifdef OLD_PINOUT
	#define R0_PIN 4
	#define G0_PIN 5
	#define B0_PIN 14
	#define R1_PIN 12
	#define G1_PIN 13
	#define B1_PIN 16
	#define CLK_PIN 22
	#define LAT_PIN 23
	#define OE_PIN 27
	#define A_PIN 17
	#define B_PIN 18
	#define C_PIN 19
	#define D_PIN 21
	#define E_PIN -1
#endif

#ifdef NEW_PINOUT
	#define R0_PIN 23
	#define G0_PIN 22
	#define B0_PIN 17
	#define R1_PIN 16
	#define G1_PIN 21
	#define B1_PIN 4
	#define CLK_PIN 14
	#define LAT_PIN 5 
	#define OE_PIN 27
	#define A_PIN 13
	#define B_PIN 19
	#define C_PIN 12
	#define D_PIN 18
	#define E_PIN -1
#endif

#define WIDTH 64
#define HEIGHT 32

#define WHITE 0xFFFF

/*
 * @brief	Initiates LED Matrix panel and clears the screen
 *
 *			Sets width, height, and brightness parameters
 *
 * @param	width in pixels
 * @param	height in pixels
 * */
void matrix_init(int width, int height);

/*
 * @brief	Clears LED Matrix 
 *
 *			turns all pixels off and wipes all data from shift registers
 * */
void matrix_clear();

/*
 * @brief	draws a pixel anywhere on display
 *
 *			shifts RGB data to a location and displays
 *
 * @param	x - x position of pixel drawn
 * @param	y - y position of pixel drawn
 * @param	color - RGB565 color used for pixel
 * */
void matrix_draw_pixel(int x, int y, uint16_t color);

/*
 * @brief	draws a row on the LED Matrix using a data buffer
 *
 *			parses uint64_t buffer which tells it which pixels to light up on a given row of a certain color
 *
 * @param	row - which row we draw to (starting 0 at the top until HEIGHT - 1 for the Bottom)
 * @param	data - uint64_t buffer containing which pixels are to be lit up
 * @param	color - RGB565 color used for the row
 * */
void matrix_draw_row(int row, uint64_t data, uint16_t color);

/*
 * @brief	draws pillar looking bars to indicate audio frequencies
 *
 *			takes a buffer of audio frequency levels, and displays them onto the matrix 
 *			
 * @param	levels - pointer to buffer containing audio frequency amplitude data
 * @param	color - RGB565 color used by the matrix
 * */
void matrix_draw_audio_levels(float* levels, uint16_t color);


#ifdef __cplusplus
}
#endif

#endif //MATRIX_WRAPPER_H
