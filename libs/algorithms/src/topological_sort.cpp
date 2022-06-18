#include <algorithms/topological_sort.hpp>



std::vector<int> algo::TopologicalSort::run(const graphics::Graph& graph) {
    m_traversal.clear();
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
    }
    m_cycle.erase(src);
    m_visited.insert(src);
    m_traversal.push_back(src);
    return true;
}