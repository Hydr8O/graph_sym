#include <algorithms/topological_sort.hpp>



algo::Traversal algo::TopologicalSort::run(const graphics::Graph& graph) {
    m_traversal.node_traversal.clear();
    m_traversal.edge_traversal.clear();
    m_visited.clear();
    m_cycle.clear();
    for (auto& [src, neighbours] : graph.get_paths()) {
        if (!dfs_helper(graph, src)) {
            return {};
        };
    }

    return m_traversal;
}

bool algo::TopologicalSort::dfs_helper(const graphics::Graph& graph, int src) {
    if (m_cycle.count(src)) {
        return false;
    }

    if (m_visited.count(src)) {
        return true;
    }

    m_cycle.insert(src);
    for (auto& dst : graph.get_paths().at(src)) {
        if (!dfs_helper(graph, dst)) {
            return false;
        }
        for (const auto& [edge_id, edge] : graph.get_edges()) {
            if (edge->get_src_id() == src && edge->get_dst_id() == dst) {
                m_traversal.edge_traversal.push_back(edge);
                break;
            }
        }
    }
    m_cycle.erase(src);
    m_visited.insert(src);
    m_traversal.node_traversal.push_back(graph.get_nodes().at(src));
    return true;
}