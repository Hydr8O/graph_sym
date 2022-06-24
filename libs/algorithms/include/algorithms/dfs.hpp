#ifndef DFS_HPP_
#define DFS_HPP_

#include <algorithms/algorithm.hpp>
#include <unordered_set>
#include <queue>


namespace algo {
    class DFS : public Algorithm {
    private:
        int m_src;
        std::unordered_set<int> m_visited;
        Traversal m_traversal;
        void dfs_helper(const graphics::Graph& graph, int src);

    public:
        DFS(int src);
        Traversal run(const graphics::Graph& graph) override;
    };

}

#endif