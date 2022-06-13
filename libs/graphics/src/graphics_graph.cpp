#include <graphics/graphics_graph.hpp>


void graphics::Graph::add_node(std::shared_ptr<Node> node) {
    m_node_id++;
    node->set_id(m_node_id);
    m_nodes[m_node_id] = node;
}

void graphics::Graph::add_edge(std::shared_ptr<graphics::Edge> edge) {
    m_edge_id++;
    edge->set_id(m_edge_id);
    m_edges[m_edge_id] = edge;
}

void graphics::Graph::add_label(std::string label) {
    m_node_labels.insert(label);
}

void graphics::Graph::remove_label(std::string label) {
    m_node_labels.erase(label);
}

void graphics::Graph::print_labels() {
    for (const std::string& label : m_node_labels) {
        std::cout << label << " ";
    }
    std::cout << std::endl;
}

const NodeArray& graphics::Graph::get_nodes() const {
    return m_nodes;
}

const EdgeArray &graphics::Graph::get_edges() const {
    return m_edges;
}

int graphics::Graph::get_next_node_id() const {
    return m_node_id;
}

bool graphics::Graph::label_exists(const std::string& label) {
    if (m_node_labels.count(label)) {
        return true;
    }

    return false;
}