#include "ESP32-HUB75-MatrixPanel-I2S-DMA.h"
#include "matrix_wrapper.h"

extern "C"
{

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

void matrix_init(int width, int height)
{
	HUB75_I2S_CFG mxconfig(width, height, 1, hub75_pins);
	mxconfig.clkphase = true;

	dma_display = new MatrixPanel_I2S_DMA(mxconfig);
	dma_display->begin();
	dma_display->setPanelBrightness(40);
	dma_display->clearScreen();
}

void matrix_clear()
{
	if(!dma_display)
	{
		return;
	}
	dma_display->clearScreen();
}

void matrix_draw_pixel(int x, int y, uint16_t color)
{
	if(!dma_display)
	{
		return;
	}
	dma_display->drawPixel(x, y, color);
}

void matrix_draw_row(int row, uint64_t data, uint16_t color)
{
	if(!dma_display)
	{
		return;
	}

	for(int i = 0; i < WIDTH; i++)
	{
		if((data >> i) & 0x1)
		{
			matrix_draw_pixel(i, row, color);
		}
	}
}

// TODO: sensitivity buttons 
void matrix_draw_audio_levels(float* levels, uint16_t color)
{
	if(!dma_display) 
	{
		return;
	}

	uint64_t rowBuffer = 0;

	for(int row = 0; row < HEIGHT; row++)
	{
		for(int bin = 0; bin < WIDTH/2; bin++)
		{
			if(levels[bin]/4 >= row) //dividing by four seems like a good sensitivity
			{
				rowBuffer |= (3ULL << (bin * 2)); //3ULL is 0b11
			}
		}
		matrix_draw_row(HEIGHT-row-1, rowBuffer, color);
		rowBuffer = 0;
	}
}
}
