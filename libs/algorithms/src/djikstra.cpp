#include <algorithms/djikstra.hpp>

algo::Djikstra::Djikstra(int src) {
    m_src = src;
}

void algo::Djikstra::init_distances(const WeightedAdjacencyList& adjacency) {
    for (auto& [src, neighbours] : adjacency) {
        m_distances[src] = MAXFLOAT;
    }
    m_distances[m_src] = 0;
}

algo::Traversal algo::Djikstra::run(const graphics::Graph& graph) {
    const WeightedAdjacencyList& adjacency = graph.get_weighted_paths();
    init_distances(adjacency);
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> min_heap;
    min_heap.push({m_distances.at(m_src), m_src});
    while (!min_heap.empty()) {
        auto [weight, src] = min_heap.top();
        min_heap.pop();
        m_visited.insert(src);
        const std::shared_ptr<Node>& node = graph.get_nodes().at(src);
        m_traversal.node_traversal.push_back(node);

        for (auto& [dst_weight, dst] : adjacency.at(src)) {
            if (!m_visited.count(dst)) {
                float new_distance = dst_weight + weight;
                if (new_distance < m_distances[dst]) {
                    min_heap.push({new_distance, dst});
                    m_distances[dst] = new_distance;
                }
            }
        }
    }


    m_traversal.distances = m_distances;

    return m_traversal;
}