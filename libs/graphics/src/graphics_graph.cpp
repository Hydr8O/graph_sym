#include <graphics/graphics_graph.hpp>


void graphics::Graph::add_node(std::shared_ptr<Node> node) {
    m_node_id++;
    node->set_id(m_node_id);
    m_nodes[m_node_id] = node;
}

void graphics::Graph::add_edge(std::shared_ptr<graphics::Edge> new_edge) {
    if (edge_exsists(new_edge)) {
        return;
    }

    m_edge_id++;
    new_edge->set_id(m_edge_id);
    m_edges[m_edge_id] = new_edge;
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

bool graphics::Graph::edge_exsists(const std::shared_ptr<graphics::Edge>& new_edge) {
    for (const auto& [edge_id, edge] : m_edges) {
        bool same_src = new_edge->get_src_id() == edge->get_src_id();
        bool same_dst = new_edge->get_dst_id() == edge->get_dst_id();
        if (same_src && same_dst) {
            return true;
        }
    }
    return false;
}