cmake_minimum_required(VERSION 3.22)

set(
    SOURCES
    src/graphics_graph.cpp
    src/node.cpp
    src/state.cpp
    src/graph_event_handler.cpp
    src/edge.cpp
)


add_library(graphics STATIC ${SOURCES})

target_include_directories(graphics PUBLIC include)
