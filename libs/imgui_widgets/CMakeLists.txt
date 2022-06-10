cmake_minimum_required(VERSION 3.22)

set(
    SOURCES
    src/list_box.cpp
    src/list_item.cpp
)


add_library(imgui_widgets STATIC ${SOURCES})

target_include_directories(imgui_widgets PRIVATE include ${CMAKE_SOURCE_DIR}/imgui)