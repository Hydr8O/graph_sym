#ifndef TOPOLOGICAL_SORT_HPP_
#define TOPOLOGICAL_SORT_HPP_

#include <algorithms/algorithm.hpp>
#include <unordered_set>
#include <queue>


namespace algo {
    class TopologicalSort : public Algorithm {
    private:
        std::unordered_set<int> m_visited;
        std::unordered_set<int> m_cycle;
        std::vector<int> m_traversal;
        bool dfs_helper(const graphics::Graph& graph, int src);

    public:
        std::vector<int> run(const graphics::Graph& graph) override;
    };

}

#endif