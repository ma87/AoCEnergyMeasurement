cmake_minimum_required(VERSION 3.10)
project(aocd14 C)

set(CMAKE_C_STANDARD 99)

add_executable(aocd14 main.c)

configure_file(input.in input.in COPYONLY)