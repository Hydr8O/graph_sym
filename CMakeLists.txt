cmake_minimum_required(VERSION 3.22)

project(
    graph_sym
    VERSION 1.0 
    DESCRIPTION "simple game for sfml practice"
    LANGUAGES CXX
)

add_subdirectory(libs)
set(
    ImGui-SFML_DIR
    build_imgui-sfml/lib/cmake/ImGui-SFML
)
find_package(ImGui-SFML REQUIRED)
add_executable(graph_sym main.cpp)
target_include_directories(
    graph_sym 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/algorithms/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/graphics/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui_widgets/include
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

target_link_libraries(graph_sym algorithms graphics imgui_widgets sfml-graphics sfml-window sfml-system ImGui-SFML::ImGui-SFML)
