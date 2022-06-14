cmake_minimum_required(VERSION 3.22)

set(
    SOURCES
    src/algo_graph.cpp
    src/algorithm_runner.cpp
)

add_library(algorithms ${SOURCES})
target_include_directories(algorithms PRIVATE include)