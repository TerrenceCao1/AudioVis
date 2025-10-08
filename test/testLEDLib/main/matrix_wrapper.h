#ifndef MATRIX_WRAPPER_H
#define MATRIX_WRAPPER_H


#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

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

#define WIDTH 64
#define HEIGHT 32

#define WHITE 0xFFFF

void matrix_init(int width, int height);
void matrix_clear();
void matrix_draw_pixel(int x, int y, uint16_t color);
void matrix_draw_row(int row, uint64_t data, uint16_t color);
void matrix_draw_audio_levels(int* levels);


#ifdef __cplusplus
}
#endif

#endif //MATRIX_WRAPPER_H
