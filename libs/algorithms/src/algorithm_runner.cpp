#include <algorithms/algorithm_runner.hpp>
#include <iostream>


algo::AlgorithmRunner::AlgorithmRunner() {}

algo::AlgorithmRunner::AlgorithmRunner(const graphics::Graph &graph) {
    m_graph = graph;
}

void algo::AlgorithmRunner::set_graph(const graphics::Graph &graph) {
    m_graph = graph;
}

void algo::AlgorithmRunner::set_algorithm(std::shared_ptr<algo::Algorithm> &algorithm) {
    m_algorithm = algorithm;
}

std::vector<int> algo::AlgorithmRunner::run_bfs(int src) {
    if (!m_graph.get_paths().count(src)) {
        return {};
    }

    m_traversal.clear();
    m_visited.clear();
    const AdjacencyList& adjacency = m_graph.get_paths();
    std::queue<int> q;
    q.push(src);

    while (!q.empty()) {
        const int current = q.front();
        q.pop();
        m_visited.insert(current);
        m_traversal.push_back(current);

        for (auto& dst : adjacency.at(current)) {
            if (!m_visited.count(dst)) {
                q.push(dst);
                m_visited.insert(dst);
            }
        }

    }
    return m_traversal;
}

std::vector<int> algo::AlgorithmRunner::run_dfs(int src) {
    if (!m_graph.get_paths().count(src)) {
        return {};
    }
    m_traversal.clear();
    m_visited.clear();
    dfs_helper(src);
    return m_traversal;
}

std::vector<int> algo::AlgorithmRunner::run_algorithm() {
    return m_algorithm->run(m_graph);
}

std::vector<int> algo::AlgorithmRunner::run_topological_sort() {
    m_traversal.clear();
    m_visited.clear();
    m_cycle.clear();
    for (auto& [src, neighbours] : m_graph.get_paths()) {
        if (!dfs_helper_topological(src)) {
            return {};
        };
    }
    return m_traversal;
}

void algo::AlgorithmRunner::dfs_helper(int src) {
    if (m_visited.count(src)) {
        return;
    }

    m_visited.insert(src);
    m_traversal.push_back(src);

    for (auto& dst : m_graph.get_paths().at(src)) {
        dfs_helper(dst);
    }
}

bool algo::AlgorithmRunner::dfs_helper_topological(int src) {
    if (m_cycle.count(src)) {
        return false;
    }

    if (m_visited.count(src)) {
        return true;
    }

    m_cycle.insert(src);
    for (auto& dst : m_graph.get_paths().at(src)) {
        if (!dfs_helper_topological(dst)) {
            return false;
        }
    }
    m_cycle.erase(src);
    m_visited.insert(src);
    m_traversal.push_back(src);
    return true;
}