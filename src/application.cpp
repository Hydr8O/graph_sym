#include <application.hpp>

Application::Application(int width, int height, std::string window_name) 
    : m_window(sf::VideoMode(width, height), window_name, sf::Style::Default), m_graph_event_handler(m_graphics_graph) {
    if (!ImGui::SFML::Init(m_window)) {
        std::cout << "Failed to init window" << std::endl;
    }
    m_window.setFramerateLimit(60);
    m_font.loadFromFile("../fonts/railway/railway.otf");
    m_graphics_graph.set_font(m_font);
}

void Application::run() {
    algo::Traversal traversal;
    algo::Traversal initial_traversal;

    while (m_window.isOpen()) {
        sf::Time dt = m_clock.restart();
        m_state.animation_state.duration += dt.asSeconds();

        handle_sfml_events();
        handle_state_update(traversal, initial_traversal);
            
        ImGui::SFML::Update(m_window, m_clock.restart());
        
        handle_imgui_events();

        m_window.clear();
        handle_sfml_drawing(initial_traversal);
       
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
    ImGui::SFML::Shutdown();
}

void Application::handle_sfml_events() {
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
    while (m_window.pollEvent(m_event)) {
        ImGui::SFML::ProcessEvent(m_window, m_event);
        switch (m_event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (io.WantCaptureMouse) {
                    break;
                } 
                m_state.ready_to_run_algorithms = false;
                if (m_event.mouseButton.button == sf::Mouse::Left) {
                    if (m_state.src_vertex_selection()) {
                        m_graph_event_handler.handle_src_vertex_selection(m_event, m_state);
                    } else if (m_state.dst_vertex_selection()) {
                        m_graph_event_handler.handle_dst_vertex_selection(m_event, m_state);
                    }

                    if (m_state.edge_connection()) {
                        m_graph_event_handler.handle_edge_connection(m_event, m_state, m_weight_input_fields);
                    }

                    if (m_state.vertex_creation()) {
                        m_graph_event_handler.handle_vertex_creation(m_event, m_state, m_input_fields);
                    }
                    
                } else if (m_event.mouseButton.button == sf::Mouse::Right) {
                    m_graph_event_handler.handle_vertex_deletion(m_event, m_state, m_input_fields);
                    m_graph_event_handler.handle_edge_deletion(m_event, m_state);
                }
        }
    }
}

void Application::handle_state_update(algo::Traversal& traversal, algo::Traversal& initial_traversal) {
    if (m_state.creation_finished) {
        m_graph_event_handler.handle_graph_creation_finish(m_event, m_state);
    }

    if (m_state.running_algorithm) {
        m_state.ready_to_run_algorithms = false;
        m_algo_runner.set_graph(m_graphics_graph);
        traversal = m_algo_runner.run_algorithm();
        initial_traversal.distances = traversal.distances;
        for (auto& [node_id, dist] : initial_traversal.distances) {
            dist = MAXFLOAT;
        }
        m_state.running_algorithm = false;
        m_state.animation_state.animation = true;
    }


    if (m_state.animation_state.animation && m_state.animation_state.duration > 0.01f && (!traversal.node_traversal.empty())) {
        m_graph_event_handler.handle_animation_step(m_event, m_state.animation_state, traversal, initial_traversal);
    }

    if (m_state.animation_state.animation && m_state.animation_state.current_animating_node >= traversal.node_traversal.size()) {
        m_graph_event_handler.handle_animation_finish(m_state.animation_state, traversal, initial_traversal);
        m_state.ready_to_run_algorithms = true;
    }
    
    if (m_state.edge_creation()) { //edge creation
        m_graph_event_handler.handle_edge_creation(m_event, m_state, m_window);
    }
}

void Application::handle_algorithm_buttons() {
    if (ImGui::Button("BFS")) {
        int starting_node_id = m_graphics_graph.map_label_to_id(m_state.algorithm_state.starting_vertex);
        std::shared_ptr<algo::Algorithm> bfs = std::make_shared<algo::BFS>(starting_node_id);
        m_algo_runner.set_algorithm(bfs);
        m_state.running_algorithm = true;
    }
    ImGui::InputText("##Start", &m_state.algorithm_state.starting_vertex);

    if (ImGui::Button("DFS")) {
        int starting_node_id = m_graphics_graph.map_label_to_id(m_state.algorithm_state.starting_vertex);
        std::shared_ptr<algo::Algorithm> dfs = std::make_shared<algo::DFS>(starting_node_id);
        m_algo_runner.set_algorithm(dfs);
        m_state.running_algorithm = true;
    }

    if (ImGui::Button("Topological sort")) {
        std::shared_ptr<algo::Algorithm> topological_sort = std::make_shared<algo::TopologicalSort>();
        m_algo_runner.set_algorithm(topological_sort);
        m_state.running_algorithm = true;
    }

    if (ImGui::Button("Djikstra")) {
        int starting_node_id = m_graphics_graph.map_label_to_id(m_state.algorithm_state.starting_vertex);
        std::shared_ptr<algo::Algorithm> djikstra = std::make_shared<algo::Djikstra>(starting_node_id);
        m_algo_runner.set_algorithm(djikstra);
        m_state.running_algorithm = true;
    }

    if (ImGui::Button("Union-find")) {
        std::shared_ptr<algo::Algorithm> union_find = std::make_shared<algo::UnionFind>();
        m_algo_runner.set_algorithm(union_find);
        m_state.running_algorithm = true;
    }
}

void Application::handle_imgui_events() {
    std::unordered_set<std::string> input_values;
    const NodeArray& nodes = m_graphics_graph.get_nodes();
    const EdgeArray& edges = m_graphics_graph.get_edges();
    ImGui::Begin("Main");
    if (ImGui::Button("Finish creation")) {
        m_state.creation_finished = true;
    }

    if (m_state.ready_to_run_algorithms) {
        handle_algorithm_buttons();
    }
    ImGui::End();

    ImGui::Begin("Mode");
    std::string mode_text = "Current Mode: " + m_modes.modes[m_state.current_mode];
    ImGui::Text(mode_text.c_str());
    if (ImGui::Button("Edge Mode")) {
        m_state.set_edge_mode();
    }

    if (ImGui::Button("Vertex Mode")) {
        m_state.set_vertex_mode();
    }
    ImGui::End();

    ImGui::Begin("Nodes");
    for (auto& [node_id, input_string] : m_input_fields) {
        std::string label = "##Text" + std::to_string(node_id);
        if (input_values.count(input_string)) {
            input_string = "";
        } else {
            input_values.insert(input_string);
        }

        if (node_id == m_state.current_selected) {
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
        const std::string& label = "##" + std::to_string(edge_id);
        std::string text = src + "->" + dst;
        ImGui::Text(text.c_str());
        float* edge_weight_input = &m_weight_input_fields.at(edge_id);
        ImGui::InputFloat(label.c_str(), edge_weight_input);
    }
    ImGui::End();
}

void Application::handle_sfml_drawing(algo::Traversal& initial_traversal) {
    const NodeArray& nodes = m_graphics_graph.get_nodes();
    const EdgeArray& edges = m_graphics_graph.get_edges();
    if (m_state.edge_creation()) {
        m_window.draw(m_state.current_edge->get_body());
    }

    for (auto& [edge_id, edge] : edges) {
        edge->set_weight(m_weight_input_fields[edge_id]);
        m_window.draw(edge->get_body());
        m_window.draw(edge->get_direction_shape());
    }

    
    for (auto& [node_id, node] : nodes) {
        node->set_text(m_input_fields[node_id], m_font);
        
        m_window.draw(node->get_body());
        m_window.draw(node->get_text());
    }

    for (auto& [node_id, distance] : initial_traversal.distances) {
        std::string text = std::to_string(distance).substr(0, 4);
        if (std::abs(distance - MAXFLOAT) < std::numeric_limits<float>::epsilon()) {
            text = "inf";
        }
        nodes.at(node_id)->set_distance(text, m_font);
        m_window.draw(nodes.at(node_id)->get_distance_text());
    }
}