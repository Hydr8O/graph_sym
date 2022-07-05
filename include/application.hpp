#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <iostream>
#include <memory>
#include <unordered_map>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui-SFML.h"
#include <cstdlib>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <algorithms/algorithm_runner.hpp>

#include <algorithms/bfs.hpp>
#include <algorithms/dfs.hpp>
#include <algorithms/topological_sort.hpp>
#include <algorithms/djikstra.hpp>
#include <algorithms/union_find.hpp>

#include <graphics/node.hpp>
#include <graphics/edge.hpp>
#include <graphics/graphics_graph.hpp>
#include <graphics/state.hpp>
#include <graphics/graph_event_handler.hpp>
#include <graphics/modes.hpp>

class Application {
private:
    sf::RenderWindow m_window;
    graphics::GraphEventHandler m_graph_event_handler;
    graphics::Graph m_graphics_graph;
    sf::Clock m_clock;
    sf::Event m_event;
    graphics::State m_state;
    sf::Font m_font;
    graphics::Modes m_modes;
    algo::AlgorithmRunner m_algo_runner;
    std::unordered_map<int, std::string> m_input_fields;
    std::unordered_map<int, float> m_weight_input_fields;

    void handle_sfml_events();
    void handle_algorithm_buttons();
    void handle_imgui_events();
    void handle_state_update(algo::Traversal& traversal, algo::Traversal& initial_traversal);
    void handle_sfml_drawing(algo::Traversal& initial_traversal);

public:
    Application(int width, int height, std::string window_name);
    void run();
};

#endif