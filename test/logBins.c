#include <stdio.h>
#include <math.h>

#define NUM_BINS 32
#define FFT_BINS 512
#define SAMPLE_RATE 44100.0
#define NYQUIST_FREQ (SAMPLE_RATE / 2.0)

int main() {
    int fft_bins_per_section[NUM_BINS];
    int fft_start_indices[NUM_BINS];
    double frequencies[NUM_BINS];
    
    // Calculate logarithmic distribution of FFT bins
    // We want the number of FFT bins per section to increase logarithmically
    double total_weight = 0.0;
    double weights[NUM_BINS];
    
    // Calculate weights using logarithmic scale
    for (int i = 0; i < NUM_BINS; i++) {
        weights[i] = pow(1.2, i); // Logarithmic growth factor
        total_weight += weights[i];
    }
    
    // Normalize weights to sum to FFT_BINS and assign integer bins
    int total_assigned = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        fft_bins_per_section[i] = (int)round((weights[i] / total_weight) * FFT_BINS);
        if (fft_bins_per_section[i] < 1) fft_bins_per_section[i] = 1; // Minimum 1 bin
        total_assigned += fft_bins_per_section[i];
    }
    
    // Adjust for rounding errors to ensure we use exactly FFT_BINS
    int difference = FFT_BINS - total_assigned;
    if (difference > 0) {
        // Add extra bins to the highest frequency sections
        for (int i = NUM_BINS - 1; i >= 0 && difference > 0; i--) {
            fft_bins_per_section[i]++;
            difference--;
        }
    } else if (difference < 0) {
        // Remove bins from the highest frequency sections
        for (int i = NUM_BINS - 1; i >= 0 && difference < 0; i--) {
            if (fft_bins_per_section[i] > 1) {
                fft_bins_per_section[i]--;
                difference++;
            }
        }
    }
    
    // Calculate starting indices and frequencies for each section
    int current_fft_bin = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        fft_start_indices[i] = current_fft_bin;
        
        // Calculate center frequency of this section
        double start_freq = (double)current_fft_bin * NYQUIST_FREQ / (FFT_BINS / 2);
        double end_freq = (double)(current_fft_bin + fft_bins_per_section[i]) * NYQUIST_FREQ / (FFT_BINS / 2);
        frequencies[i] = (start_freq + end_freq) / 2.0; // Arithmetic mean
        
        current_fft_bin += fft_bins_per_section[i];
    }
    
    printf("FFT Bin Mapping for Logarithmic Audio Bins\n");
    printf("FFT Bins: %d, Output Bins: %d\n", FFT_BINS, NUM_BINS);
    printf("Sample Rate: %.1f Hz, Nyquist: %.1f Hz\n\n", SAMPLE_RATE, NYQUIST_FREQ);
    
    printf("Bin | FFT Range      | Count | Center Freq | Freq Range\n");
    printf("----|----------------|-------|-------------|------------------\n");
    
    int verification_total = 0;
    for (int i = 0; i < NUM_BINS; i++) {
        int end_index = fft_start_indices[i] + fft_bins_per_section[i] - 1;
        double start_freq = (double)fft_start_indices[i] * NYQUIST_FREQ / (FFT_BINS / 2);
        double end_freq = (double)(end_index + 1) * NYQUIST_FREQ / (FFT_BINS / 2);
        
        printf("%2d  | %3d - %3d      | %5d | %8.1f Hz | %6.1f - %6.1f Hz\n",
               i + 1, fft_start_indices[i], end_index, 
               fft_bins_per_section[i], frequencies[i], start_freq, end_freq);
        
        verification_total += fft_bins_per_section[i];
    }
    
    printf("\nTotal FFT bins used: %d (should be %d)\n\n", verification_total, FFT_BINS);
    
    // Output arrays for use in code
    printf("int fft_bins_per_section[%d] = {\n    ", NUM_BINS);
    for (int i = 0; i < NUM_BINS; i++) {
        printf("%d", fft_bins_per_section[i]);
        if (i < NUM_BINS - 1) printf(", ");
        if ((i + 1) % 8 == 0 && i < NUM_BINS - 1) printf("\n    ");
    }
    printf("\n};\n\n");
    
    printf("int fft_start_indices[%d] = {\n    ", NUM_BINS);
    for (int i = 0; i < NUM_BINS; i++) {
        printf("%d", fft_start_indices[i]);
        if (i < NUM_BINS - 1) printf(", ");
        if ((i + 1) % 8 == 0 && i < NUM_BINS - 1) printf("\n    ");
    }
    printf("\n};\n");
    
    return 0;
}