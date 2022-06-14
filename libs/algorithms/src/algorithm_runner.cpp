#include <algorithms/algorithm_runner.hpp>
#include <iostream>


algo::AlgorithmRunner::AlgorithmRunner() {}

algo::AlgorithmRunner::AlgorithmRunner(const algo::Graph &algo_graph) {
    m_algo_graph = algo_graph;
}

void algo::AlgorithmRunner::set_graph(const algo::Graph &algo_graph) {
    m_algo_graph = algo_graph;
}

std::vector<std::string> algo::AlgorithmRunner::run_bfs(const std::string& src) {
    std::unordered_set<std::string> visited;
    std::vector<std::string> traversal;
    const AdjacencyList& adjacency = m_algo_graph.get_edges();
    std::queue<std::string> q;
    q.push(src);

    while (!q.empty()) {
        const std::string current = q.front();
        q.pop();
        visited.insert(current);
        traversal.push_back(current);

        for (auto& dst : adjacency.at(current)) {
            if (!visited.count(dst)) {
                q.push(dst);
                visited.insert(dst);
            }
        }

    }
    return traversal;
}