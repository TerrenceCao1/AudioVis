# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

cmake_minimum_required(VERSION 3.12)

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})
