#ifndef ALGORITHM_RUNNER_HPP_
#define ALGORITHM_RUNNER_HPP_

#include <queue>
#include <graphics/graphics_graph.hpp>
#include <unordered_set>
#include <vector>


namespace algo {
    class AlgorithmRunner {
    private:
        graphics::Graph m_graph;
        std::unordered_set<int> m_visited;
        std::vector<int> m_traversal;
        void dfs_helper(int src);
    public:
        AlgorithmRunner(const graphics::Graph& graphics_graph);
        AlgorithmRunner();
        void set_graph(const graphics::Graph& graphics_graph);
        std::vector<int> run_bfs(int src);
        std::vector<int> run_dfs(int src);
    };
}


#endif