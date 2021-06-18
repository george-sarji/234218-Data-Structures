cmake_minimum_required(VERSION 3.0.0)
project(234218_data_structures C CXX)

set(FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(FLAGS_RELEASE "${FLAGS_DEBUG} -DNDEBUG")
set(CMAKE_C_FLAGS ${FLAGS_DEBUG})
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(agency Agency.cpp SetManager.cpp AgencyManager.cpp Exception.cpp CarType.cpp CarSale.cpp TreeException.cpp main.cpp)