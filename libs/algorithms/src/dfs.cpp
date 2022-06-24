#include <algorithms/dfs.hpp>



algo::DFS::DFS(int src) {
    m_src = src;
}

algo::Traversal algo::DFS::run(const graphics::Graph& graph) {
    if (!graph.get_paths().count(m_src)) {
        return {};
    }
    m_traversal.node_traversal.clear();
    m_traversal.edge_traversal.clear();
    m_visited.clear();
    dfs_helper(graph, m_src);
    return m_traversal;
}

void algo::DFS::dfs_helper(const graphics::Graph& graph, int src) {
    if (m_visited.count(src)) {
        return;
    }

    m_visited.insert(src);
    m_traversal.node_traversal.push_back(graph.get_nodes().at(src));

    for (auto& dst : graph.get_paths().at(src)) {
        if (!m_visited.count(dst)) {
            for (const auto& [edge_id, edge] : graph.get_edges()) {
                if (edge->get_src_id() == src && edge->get_dst_id() == dst) {
                    m_traversal.edge_traversal.push_back(edge);
                    break;
                }
            }
        }
        dfs_helper(graph, dst);
    }
}