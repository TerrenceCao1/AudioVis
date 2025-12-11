#include <stdio.h>
#include <math.h>

#define FFT_BANDS 32
#define MIN_BAND_VALUE 2
#define MAX_BAND_VALUE 32

int main(void)
{
	int bandBins[FFT_BANDS+1]; //number of bands + 1 for edges
	bandBins[0] = MIN_BAND_VALUE;
	for(int i = 1; i < FFT_BANDS+1; i++)
	{
		double ratio = (double)i/FFT_BANDS;
		double value = MIN_BAND_VALUE * pow((double)MAX_BAND_VALUE/MIN_BAND_VALUE, ratio);

		bandBins[i] = (int)round(value);

		if(bandBins[i] <= bandBins[i-1])
		{
			bandBins[i] = bandBins[i-1] + 1;
		}
	}

	for(int i = 0; i < FFT_BANDS+1;i++)
	{
		printf("Bin %i: %i\n", i, bandBins[i]);
	}
}
