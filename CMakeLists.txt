cmake_minimum_required(VERSION 3.12)
project(libhosts C)

set(CMAKE_C_STANDARD 99)

add_executable(libhosts test.c hashmap.c parser.c)