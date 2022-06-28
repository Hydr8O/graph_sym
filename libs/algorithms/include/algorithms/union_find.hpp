#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <algorithms/algorithm.hpp>

namespace algo {
    class UnionFind : public Algorithm {
    private:
        Traversal m_traversal;
        std::unordered_map<int, int> m_parents;
        std::unordered_map<int, int> m_rank;
        int find(int node);
        bool make_union(int node1, int node2);
    public:
        Traversal run(const graphics::Graph& graph) override;
    };
}

#endif