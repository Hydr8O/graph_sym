#include <algorithms/bfs.hpp>



algo::BFS::BFS(int src) {
    m_src = src;
}

algo::Traversal algo::BFS::run(const graphics::Graph& graph) {
    if (!graph.get_paths().count(m_src)) {
        return {};
    }

    m_traversal.node_traversal.clear();
    m_traversal.edge_traversal.clear();
    m_visited.clear();
    const AdjacencyList& adjacency = graph.get_paths();
    std::queue<int> q;
    q.push(m_src);

    while (!q.empty()) {
        const int current = q.front();
        q.pop();
        m_visited.insert(current);
        m_traversal.node_traversal.push_back(graph.get_nodes().at(current));

        for (auto& dst : adjacency.at(current)) {
            if (!m_visited.count(dst)) {
                for (const auto& [edge_id, edge] : graph.get_edges()) {
                    if (edge->get_src_id() == current && edge->get_dst_id() == dst) {
                        m_traversal.edge_traversal.push_back(edge);
                        break;
                    }
                }
                q.push(dst);
                m_visited.insert(dst);
            }
        }

    }

    // for (int i = 1; i < m_traversal.node_traversal.size(); i++) {
    //     int src = m_traversal.node_traversal[i - 1]->get_id();

    //     int dst = m_traversal.node_traversal[i]->get_id();

    //     for (const auto& [edge_id, edge] : graph.get_edges()) {
    //         if (edge->get_src_id() == src && edge->get_dst_id() == dst) {
    //             m_traversal.edge_traversal.push_back(edge);
    //             break;
    //         }
    //     }
        
    // }
    return m_traversal;
}
