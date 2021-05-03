cmake_minimum_required(VERSION 3.0.0)
project(234218_data_structures C CXX)

set(LAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(FLAGS_RELEASE "${FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(ASSIGNMENT_1 "Assignments/hw1")

# add_executable(hw0-part1 Assignments/hw0/part1.c)
link_directories(.)