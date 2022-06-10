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

#include <algorithms/algo_graph.hpp>
#include <graphics/node.hpp>
#include <graphics/graphics_graph.hpp>
#include <graphics/state.hpp>
#include <graphics/graph_event_handler.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML", sf::Style::Default);
    ImGui::SFML::Init(window);
    sf::Event event;
    graphics::State state;
    algo::Graph algo_graph;
    graphics::Graph graphics_graph;
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

    bool creating_node = false;
    std::vector<std::string> nodes = algo_graph.get_nodes();
    std::cout << nodes.size() << std::endl;
    sf::VertexArray line(sf::Lines, 2);
    
    bool mouse_pressed = false;
    while (window.isOpen()) {
        sf::Event event;
        ImGuiIO& io = ImGui::GetIO();
        const NodeArray& nodes = graphics_graph.get_nodes();

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
                    
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (state.src_vertex_selection()) {
                            graph_event_handler.handle_src_vertex_selection(event, state);
                        } else if (state.dst_vertex_selection()) {
                            graph_event_handler.handle_dst_vertex_selection(event, state);
                        }

                        if (state.edge_connection()) {
                            graph_event_handler.handle_edge_connection(event, state, line);
                        }

                        if (state.vertex_creation()) {
                            graph_event_handler.handle_vertex_creation(event, state, font, input_fields);
                        }
                    }
            } 

            if (state.vertex_mode()) {
                line[0].position = {0.f, 0.f};
                line[1].position = {0.f, 0.f};
            }

            
            if (state.edge_creation()) { //edge creation
                graph_event_handler.handle_edge_creation(event, state, window, line);
            }
            
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        std::unordered_set<std::string> input_values;
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
        
        ImGui::End();

        window.clear();
        window.draw(line);
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