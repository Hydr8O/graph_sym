#include <algorithms/union_find.hpp>

algo::Traversal algo::UnionFind::run(const graphics::Graph &graph) {
    const AdjacencyList& adjacency = graph.get_paths();
    const EdgeArray& edges = graph.get_edges();
    const NodeArray& nodes = graph.get_nodes();
    m_traversal.node_traversal.clear();
    m_traversal.edge_traversal.clear();
    m_traversal.distances.clear();

    for (auto& [src, neighbours] : adjacency) {
        m_parents[src] = src;
        m_rank[src] = 1;
    }

    for (auto& [edge_id, edge] : edges) {
        int src = edge->get_src_id();
        int dst = edge->get_dst_id();
        if (!make_union(src, dst)) {
            m_traversal.node_traversal.clear();
            m_traversal.edge_traversal.clear();
            m_traversal.node_traversal.push_back(nullptr);
            m_traversal.edge_traversal.push_back(edge);
            return m_traversal;
        };

        m_traversal.node_traversal.push_back(nodes.at(src));
        m_traversal.node_traversal.push_back(nodes.at(dst));
        m_traversal.edge_traversal.push_back(edge);
    }

    return m_traversal;
}

int algo::UnionFind::find(int node) {
    int parent = m_parents[node];

    while (parent != m_parents[parent]) {
        parent = m_parents[parent];
        m_parents[parent] = m_parents[m_parents[parent]];
    }

    return parent;
}

bool algo::UnionFind::make_union(int node1, int node2) {
    int parent1 = find(node1);
    int parent2 = find(node2);

    if (parent1 == parent2) {
        return false;
    }

    if (m_rank[parent1] > m_rank[parent2]) {
        m_parents[parent2] = parent1;
        m_rank[parent1]++;
    } else {
        m_parents[parent1] = parent2;
        m_rank[parent2]++;
    }

    return true;
}