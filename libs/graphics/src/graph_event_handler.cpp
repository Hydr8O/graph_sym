#include <graphics/graph_event_handler.hpp>

void graphics::GraphEventHandler::handle_src_vertex_selection(const sf::Event& event, graphics::State& state) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    const NodeArray& nodes = m_graph.get_nodes();
    for (const auto& [node_id, node] : nodes) {
        if (node->clicked(x, y)) {
            state.current_selected = node->get_id();
            node->set_color(sf::Color::Green);
        } else {
            node->set_color(sf::Color::White);
        }
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

void graphics::GraphEventHandler::handle_edge_connection(const sf::Event &event, graphics::State &state, sf::VertexArray& line) {
    const NodeArray& nodes = m_graph.get_nodes();
    int dst_node = state.current_dst;
    const sf::Vector2f& node_position = nodes.at(dst_node)->get_body().getPosition();
    line[1].position = node_position;
    state.current_dst = -1;
}

void graphics::GraphEventHandler::handle_vertex_creation(const sf::Event &event, graphics::State &state, const sf::Font& font, std::unordered_map<int, std::string>& input_fields) {
    float x = event.mouseButton.x;
    float y = event.mouseButton.y;
    std::shared_ptr<Node> node = std::make_shared<Node>();    
    node->set_body(30.f);
    node->set_position(x, y);
    m_graph.add_node(node);
    int node_id = node->get_id();
    node->set_text(std::to_string(node_id), font);
    input_fields[node_id] = std::to_string(node_id);
}

void graphics::GraphEventHandler::handle_edge_creation(const sf::Event &event, graphics::State &state, const sf::RenderWindow& window, sf::VertexArray& line) {
    const NodeArray& nodes = m_graph.get_nodes();
    int current_selected = state.current_selected;
    const sf::Vector2f& node_position = nodes.at(current_selected)->get_body().getPosition();
    const sf::Vector2i& mouse_position = sf::Mouse::getPosition(window);
    line[0].position = node_position;
    line[1].position = window.mapPixelToCoords(mouse_position);
}