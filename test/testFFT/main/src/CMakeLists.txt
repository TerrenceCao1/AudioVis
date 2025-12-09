# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

cmake_minimum_required(VERSION 3.30)

idf_component_register(
    SRCS
        "main.c"
        "Audio_task.c"
		"../../components/esp32-fft/components/fft/fft.c"
    INCLUDE_DIRS
        "../include"
		"../../components/esp32-fft/components/fft/include"
    REQUIRES
        driver
        freertos
)
