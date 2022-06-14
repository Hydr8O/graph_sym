#include <algorithm>
#include <iostream>
#include <algorithms/algo_graph.hpp>


algo::Graph::Graph() {

}

algo::Graph::~Graph() {

}

void algo::Graph::add_edge(std::string src, std::string dst) {
    if (!m_adjacency_list.count(src)) {
        m_n_nodes++;
    }

    if (!m_adjacency_list.count(dst)) {
        m_n_nodes++;
    }

    m_adjacency_list[src].push_back(dst);
    if (!m_adjacency_list.count(dst)) {
        m_adjacency_list[dst] = {};
    }
}

void algo::Graph::remove_edge(std::string src, std::string dst) {
    if (m_adjacency_list.count(src)) {
        std::vector<std::string>& adjacent_nodes =  m_adjacency_list[src];
        auto it = std::find(adjacent_nodes.begin(), adjacent_nodes.end(), dst);

        if (it == adjacent_nodes.end()) {
            return;
        }

        adjacent_nodes.erase(it);
    }
}

std::vector<std::string> algo::Graph::get_nodes() {
    std::vector<std::string> nodes;
    for (auto [node, neighbours] : m_adjacency_list) {
        nodes.push_back(node);
    }

    return nodes;
}

AdjacencyList algo::Graph::get_edges() const {
    return m_adjacency_list;
}