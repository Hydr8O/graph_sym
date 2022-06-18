#include <algorithms/dfs.hpp>



algo::DFS::DFS(int src) {
    m_src = src;
}

std::vector<int> algo::DFS::run(const graphics::Graph& graph) {
    if (!graph.get_paths().count(m_src)) {
        return {};
    }
    m_traversal.clear();
    m_visited.clear();
    dfs_helper(graph, m_src);
    return m_traversal;
}

void algo::DFS::dfs_helper(const graphics::Graph& graph, int src) {
    if (m_visited.count(src)) {
        return;
    }

    m_visited.insert(src);
    m_traversal.push_back(src);

    for (auto& dst : graph.get_paths().at(src)) {
        dfs_helper(graph, dst);
    }
}