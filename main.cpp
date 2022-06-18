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

#include <graphics/node.hpp>
#include <graphics/edge.hpp>
#include <graphics/graphics_graph.hpp>
#include <graphics/state.hpp>
#include <graphics/graph_event_handler.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1020

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML", sf::Style::Default);
    if (!ImGui::SFML::Init(window)) {
        std::cout << "Failed to init window" << std::endl;
    }
    sf::Event event;
    sf::Clock clock;
    float duration = 0.f;
    graphics::State state;
    sf::Color animation_color;
    std::vector<int> traversal;
    int red = 255, green = 255;
    graphics::Graph graphics_graph;
    std::string starting_vertex = "1";
    int current_animating_node = 0;
    algo::AlgorithmRunner algo_runner;
    graphics::GraphEventHandler graph_event_handler(graphics_graph);
    std::unordered_map<graphics::Mode, std::string> modes;
    modes[graphics::VertexMode] = "Vertex";
    modes[graphics::EdgeMode] = "Edge";
    std::unordered_map<int, std::unordered_set<int>> adjacency; 
    window.setFramerateLimit(60);
    sf::Clock deltaClock;
    sf::Font font;
    
    font.loadFromFile("../fonts/railway/railway.otf");
    std::unordered_map<int, std::string> input_fields;

    graphics::Edge edge;
    
    bool mouse_pressed = false;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        duration += dt.asSeconds();
        sf::Event event;
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
        const NodeArray& nodes = graphics_graph.get_nodes();
        const EdgeArray& edges = graphics_graph.get_edges();

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (io.WantCaptureMouse) {
                        break;
                    } 
                    state.ready_to_run_algorithms = false;
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (state.src_vertex_selection()) {
                            graph_event_handler.handle_src_vertex_selection(event, state);
                        } else if (state.dst_vertex_selection()) {
                            graph_event_handler.handle_dst_vertex_selection(event, state);
                        }

                        if (state.edge_connection()) {
                            graph_event_handler.handle_edge_connection(event, state);
                        }

                        if (state.vertex_creation()) {
                            graph_event_handler.handle_vertex_creation(event, state, font, input_fields);
                        }
                        
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        graph_event_handler.handle_vertex_deletion(event, state, input_fields);
                        std::cout << "Event handled" << std::endl;
                    }


            }
        }

        if (state.vertex_mode()) {
            edge.reset_position();
        }

        if (state.creation_finished) {
            graphics_graph.create_adjacency_list();
            
            state.creation_finished = false;
            state.ready_to_run_algorithms = true;
        }

        if (state.running_algorithm) {
            state.ready_to_run_algorithms = false;
            algo_runner.set_graph(graphics_graph);
            traversal = algo_runner.run_algorithm();
            state.running_algorithm = false;
            state.animation = true;
        }


        if (state.animation && duration > 0.01f && !traversal.empty()) {
            red -= 5;
            green -= 5;
            if (red > 0 && green > 0) {
                duration = 0;
                animation_color = sf::Color(red, green, 255, 255);
                const std::shared_ptr<Node>& node = nodes.at(traversal[current_animating_node]);
                node->set_color(animation_color);
            } else {
                red = 255;
                green = 255;
                current_animating_node++;
            }
        }

        if (state.animation && current_animating_node >= traversal.size()) {
            std::shared_ptr<Node> node;
            for (int node_id : traversal) {
                node = nodes.at(node_id);
                node->set_color(sf::Color::White);
            }
            state.animation = false;
            state.ready_to_run_algorithms = true;
            traversal.clear();
            current_animating_node = 0;
        }
        

        if (state.edge_creation()) { //edge creation
            graph_event_handler.handle_edge_creation(event, state, window);
        }
            
        ImGui::SFML::Update(window, deltaClock.restart());
        std::unordered_set<std::string> input_values;
        ImGui::Begin("Main");
        if (ImGui::Button("Finish creation")) {
            state.creation_finished = true;
        }

        if (state.ready_to_run_algorithms) {
            if (ImGui::Button("BFS")) {
                int starting_node_id = graphics_graph.map_label_to_id(starting_vertex);
                std::shared_ptr<algo::Algorithm> bfs = std::make_shared<algo::BFS>(starting_node_id);
                algo_runner.set_algorithm(bfs);
                state.running_algorithm = true;
            }
            ImGui::InputText("##Start", &starting_vertex);

            if (ImGui::Button("DFS")) {
                int starting_node_id = graphics_graph.map_label_to_id(starting_vertex);
                std::shared_ptr<algo::Algorithm> dfs = std::make_shared<algo::DFS>(starting_node_id);
                algo_runner.set_algorithm(dfs);
                state.running_algorithm = true;
            }

            if (ImGui::Button("Topological sort")) {
                std::shared_ptr<algo::Algorithm> topological_sort = std::make_shared<algo::TopologicalSort>();
                algo_runner.set_algorithm(topological_sort);
                state.running_algorithm = true;
            }
        }
        ImGui::End();

        ImGui::Begin("Mode");
        std::string mode_text = "Current Mode: " + modes[state.current_mode];
        ImGui::Text(mode_text.c_str());
        if (ImGui::Button("Edge Mode")) {
            state.set_edge_mode();
        }

        if (ImGui::Button("Vertex Mode")) {
            state.set_vertex_mode();
        }

        ImGui::End();
        ImGui::Begin("Nodes");
        for (auto& [node_id, input_string] : input_fields) {
            std::string label = "##Text" + std::to_string(node_id);
            if (input_values.count(input_string)) {
                input_string = "";
            } else {
                input_values.insert(input_string);
            }

            if (node_id == state.current_selected) {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0,255,0,255));
                ImGui::InputText(label.c_str(), &input_string);
                ImGui::PopStyleColor();
            } else {
                ImGui::InputText(label.c_str(), &input_string);
            }

            if (input_string.size() > 1) {
                input_string = input_string.substr(0, 1);
            }
        }
        ImGui::End();
        ImGui::Begin("Edges");
        for (auto& [edge_id, edge] : edges) {
            const std::string& src = nodes.at(edge->get_src_id())->get_text().getString();
            const std::string& dst = nodes.at(edge->get_dst_id())->get_text().getString();
            std::string text = src + "->" + dst;
            ImGui::Text(text.c_str());
        }
        ImGui::End();

        window.clear();

        if (state.edge_creation()) {
            window.draw(state.current_edge->get_body());
        }

        for (auto& [edge_id, edge] : edges) {
            window.draw(edge->get_body());
        }
        
        for (auto& [node_id, node] : nodes) {
            node->set_text(input_fields[node_id], font);
            
            window.draw(node->get_body());
            window.draw(node->get_text());
        }
       
        ImGui::SFML::Render(window);
        window.display();
    }
     ImGui::SFML::Shutdown();

    return 0;
}