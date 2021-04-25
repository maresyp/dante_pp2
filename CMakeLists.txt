cmake_minimum_required(VERSION 3.17)
project(dante_pp2 C)

set(CMAKE_C_STANDARD 99)

add_executable(dante_pp2 main.c archiwum/file_utils.h archiwum/file_utils.c file_struct_utils.h file_struct_utils.c circular_buffer.h circular_buffer.c array.c array.h)