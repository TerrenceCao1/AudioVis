# Audio Visualizer
This is a summer firmware project by Josh Jin and Terrence Cao, the goal is to create an Audio Visualizer (obviously by the title)

## Components:
### INMP441 Microphone:
This microphone will take input and use the I2S communication protocol to transmit audio data to the...

### ESP32:
The ESP32 is the brains of the operation. We'll use it to parse data from the microphone and apply a Fast Fourier Transform to the audio data to figure out the specific frequencies of the current audio. It will also interface with the...

### LED Matrix:
We'll use this display to VISUALIZE the audio. 