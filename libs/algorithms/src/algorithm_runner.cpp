#include <algorithms/algorithm_runner.hpp>
#include <iostream>


algo::AlgorithmRunner::AlgorithmRunner() {}

algo::AlgorithmRunner::AlgorithmRunner(const graphics::Graph &graph) {
    m_graph = graph;
}

void algo::AlgorithmRunner::set_graph(const graphics::Graph &graph) {
    m_graph = graph;
}

std::vector<int> algo::AlgorithmRunner::run_bfs(int src) {
    std::unordered_set<int> visited;
    std::vector<int> traversal;
    const AdjacencyList& adjacency = m_graph.get_paths();
    std::queue<int> q;
    q.push(src);

    while (!q.empty()) {
        const int current = q.front();
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