# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

cmake_minimum_required(VERSION 3.30)

idf_component_register(
    SRCS
        "main.c"
        "Audio_task.c"
        "LED_task.c"
    INCLUDE_DIRS
        "../include"
    REQUIRES
        driver
        freertos
)
