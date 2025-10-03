#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"

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

MatrixPanel_I2S_DMA *dma_display = nullptr;

HUB75_I2S_CFG::i2s_pins hub75_pins = 
{
	.r1 = R0_PIN,
	.g1 = G0_PIN,
	.b1 = B0_PIN,
	.r2 = R1_PIN,
	.g2 = G1_PIN,
	.b2 = B1_PIN,

	.a = A_PIN,
	.b = B_PIN,
	.c = C_PIN,
	.d = D_PIN,
	.e = E_PIN,

	.lat = LAT_PIN,
	.oe = OE_PIN,
	.clk = CLK_PIN
};

extern "C" void app_main() {
	HUB75_I2S_CFG mxconfig(WIDTH, HEIGHT, 1, hub75_pins);
	mxconfig.clkphase = true;
	
	dma_display = new MatrixPanel_I2S_DMA(mxconfig);
	dma_display->begin();
	dma_display->setBrightness8(80);
	dma_display->clearScreen();

	dma_display->fillRect(0, 0, 2, HEIGHT, dma_display->color565(255, 255, 255));
}
