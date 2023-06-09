cmake_minimum_required(VERSION 3.25)
project(Basic_File_System C)

set(CMAKE_C_STANDARD 99)

add_executable(Basic_File_System src/main.c src/timestamps.c src/timestamps.h)
