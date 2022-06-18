#include <algorithms/bfs.hpp>



algo::BFS::BFS(int src) {
    m_src = src;
}

std::vector<int> algo::BFS::run(const graphics::Graph& graph) {
    if (!graph.get_paths().count(m_src)) {
        return {};
    }

    m_traversal.clear();
    m_visited.clear();
    const AdjacencyList& adjacency = graph.get_paths();
    std::queue<int> q;
    q.push(m_src);

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
