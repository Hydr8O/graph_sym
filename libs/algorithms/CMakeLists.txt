cmake_minimum_required(VERSION 3.22)

set(
    SOURCES
    src/algorithm_runner.cpp
)

add_library(algorithms ${SOURCES})
target_include_directories(algorithms PUBLIC include ${CMAKE_SOURCE_DIR}/libs/graphics/include)