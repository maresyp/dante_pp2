cmake_minimum_required(VERSION 3.19)
project(dante_p2 C)

set(CMAKE_C_STANDARD 99)

add_executable(dante_p2 main.c image_utils.c image_utils.h matrix_utils.c matrix_utils.h format_type.c format_type.h for_loop.c for_loop.h comparators.c comparators.h big_numbers.c big_numbers.h functions.c functions.h doubly_linked_list.c doubly_linked_list.h)