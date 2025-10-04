# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

cmake_minimum_required(VERSION 3.28)

idf_component_register(
    SRCS
		"main.c"
		"Audio_task.c"
		"LED_task.c"
		"../../components/esp32-fft/components/fft/fft.c"
    INCLUDE_DIRS
        "../include"
		"../../components/esp32-fft/components/fft/include"
    REQUIRES
        driver
        freertos
		ESP32-HUB75-MatrixPanel-DMA
)
