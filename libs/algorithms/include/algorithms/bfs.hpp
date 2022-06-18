#ifndef BFS_HPP_
#define BFS_HPP_

#include <algorithms/algorithm.hpp>
#include <unordered_set>
#include <queue>


namespace algo {
    class BFS : public Algorithm {
    private:
        int m_src;
        std::unordered_set<int> m_visited;
        std::vector<int> m_traversal;

    public:
        BFS(int src);
        std::vector<int> run(const graphics::Graph& graph) override;
    };

}

#endif