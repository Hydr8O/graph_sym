#include <graphics/graph_event_handler.hpp>

void graphics::GraphEventHandler::handle_src_vertex_selection(const sf::Event& event, graphics::State& state) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    const NodeArray& nodes = m_graph.get_nodes();
    bool any_selected = false;
    for (const auto& [node_id, node] : nodes) {
        if (node->clicked(x, y)) {
            state.current_selected = node->get_id();
            any_selected = true;
            node->set_color(sf::Color::Green);
        } else {
            node->set_color(sf::Color::White);
        }
    }

    if (!any_selected) {
        state.current_selected = -1;
    }
}

void graphics::GraphEventHandler::handle_dst_vertex_selection(const sf::Event& event, graphics::State& state) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    const NodeArray& nodes = m_graph.get_nodes();
    for (const auto& [node_id, node] : nodes) {
        if (node->clicked(x, y)) {
            state.current_dst = node_id;
            nodes.at(state.current_selected)->set_color(sf::Color::White);
            state.current_selected = -1;
        }
    }
}

void graphics::GraphEventHandler::handle_edge_connection(const sf::Event &event, graphics::State &state, std::unordered_map<int, float>& weight_input_fields) {
    const NodeArray& nodes = m_graph.get_nodes();
    const EdgeArray& edges = m_graph.get_edges();
    int dst_node_id = state.current_dst;
    std::shared_ptr<Node> dst_node = nodes.at(dst_node_id);
    const sf::Vector2f& node_position = dst_node->get_body().getPosition();
    state.current_edge->set_dst_position(node_position);
    state.current_edge->set_dst_id(dst_node->get_id());
    m_graph.add_edge(state.current_edge);
    weight_input_fields[state.current_edge->get_id()] = 0.f;
    state.current_edge = nullptr;
    state.current_dst = -1;
}

void graphics::GraphEventHandler::handle_graph_creation_finish(const sf::Event &event, graphics::State &state) {
    m_graph.create_adjacency_list();
    m_graph.create_weighted_adjacency_list();
    
    state.creation_finished = false;
    state.ready_to_run_algorithms = true;
}

void graphics::GraphEventHandler::handle_animation_step(const sf::Event &event, graphics::AnimationState &state, algo::Traversal& traversal, algo::Traversal& initial_traversal) {
    state.red -= 5;
    state.green -= 5;
    if (state.red > 0 && state.green > 0) {
        state.duration = 0;
        state.animation_color = sf::Color(state.red, state.green, 255, 255);
        const std::shared_ptr<Node>& node = traversal.node_traversal.at(state.current_animating_node);
        std::shared_ptr<graphics::Edge> edge = nullptr;
        if (state.current_animating_node < traversal.edge_traversal.size()) {
            edge = traversal.edge_traversal[state.current_animating_node];
        };
        
        if (node != nullptr) {
            node->set_color(state.animation_color);
        } else {
            state.animation_color = sf::Color::Red;
            // handle_animation_finish(state, traversal, initial_traversal);
        }

        if (edge != nullptr) {
            std::cout << edge->get_id() << std::endl;
            edge->set_color(state.animation_color);
        }
    } else {
        const std::shared_ptr<Node>& node = traversal.node_traversal.at(state.current_animating_node);
        if (node != nullptr) {
            int current_animating_node_id = traversal.node_traversal[state.current_animating_node]->get_id();
            initial_traversal.distances[current_animating_node_id] = traversal.distances[current_animating_node_id];
        }
        state.red = 255;
        state.green = 255;
        state.current_animating_node++;
    }
}

void graphics::GraphEventHandler::handle_animation_finish(graphics::AnimationState &state, algo::Traversal &traversal, algo::Traversal &initial_traversal) {
    for (const auto& node : traversal.node_traversal) {
        if (node != nullptr) {
            node->set_color(sf::Color::White);
        }
    }

    for (const auto& edge : traversal.edge_traversal) {
        std::cout << "Setting edge to white: " << edge->get_id() << std::endl;
        edge->set_color(sf::Color::White);
    }

    state.animation = false;
    traversal.node_traversal.clear();
    traversal.edge_traversal.clear();
    traversal.distances.clear();
    initial_traversal.distances.clear();
    state.current_animating_node = 0;
}

void graphics::GraphEventHandler::handle_vertex_creation(const sf::Event &event, graphics::State &state, std::unordered_map<int, std::string>& input_fields) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    std::shared_ptr<Node> node = std::make_shared<Node>();    
    node->set_body(30.f);
    node->init_text_style();
    m_graph.add_node(node);
    int node_id = node->get_id();
    node->set_text(std::to_string(node_id), m_graph.get_font());
    node->set_position(x, y);
    input_fields[node_id] = std::to_string(node_id);
}

void graphics::GraphEventHandler::handle_vertex_deletion(const sf::Event &event, graphics::State &state, std::unordered_map<int, std::string>& input_fields) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    const NodeArray& nodes = m_graph.get_nodes();
    int node_for_removal_id = -1;
    for (const auto& [node_id, node] : nodes) {
        if (node->clicked(x, y)) {
            node_for_removal_id = node_id;
            break;
        }
    }

    if (node_for_removal_id != -1) {
        m_graph.remove_node(node_for_removal_id);
        m_graph.remove_edges(node_for_removal_id);

        auto it = input_fields.find(node_for_removal_id);
        if (it != input_fields.end()) {
            input_fields.erase(it);
        }
    }
}

void graphics::GraphEventHandler::handle_edge_deletion(const sf::Event &event, graphics::State &state) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    const EdgeArray& edges = m_graph.get_edges();
    int edge_for_removal_id = -1;
    for (const auto& [edge_id, edge] : edges) {
        if (edge->clicked(x, y)) {
            edge_for_removal_id = edge_id;
        }
    }

    if (edge_for_removal_id != -1) {
        m_graph.remove_edge(edge_for_removal_id);
    }

}

void graphics::GraphEventHandler::handle_edge_creation(const sf::Event &event, graphics::State &state, const sf::RenderWindow& window) {
    const NodeArray& nodes = m_graph.get_nodes();
    int current_selected = state.current_selected;
    const std::shared_ptr<Node> current_node = nodes.at(current_selected);
    const sf::Vector2f& node_position = current_node->get_body().getPosition();
    const sf::Vector2i& mouse_position = sf::Mouse::getPosition(window);
    state.current_edge->set_src_position(node_position);
    state.current_edge->set_src_id(current_node->get_id());
    state.current_edge->set_dst_position(window.mapPixelToCoords(mouse_position));
}