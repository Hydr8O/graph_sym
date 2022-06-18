#ifndef ALGORITHM_RUNNER_HPP_
#define ALGORITHM_RUNNER_HPP_

#include <queue>
#include <unordered_set>
#include <vector>
#include <memory>

#include <graphics/graphics_graph.hpp>
#include <algorithms/algorithm.hpp>



namespace algo {
    class AlgorithmRunner {
    private:
        graphics::Graph m_graph;
        std::unordered_set<int> m_visited;
        std::unordered_set<int> m_cycle;
        std::vector<int> m_traversal;
        std::shared_ptr<Algorithm> m_algorithm;
        void dfs_helper(int src);
        bool dfs_helper_topological(int src);
    public:
        AlgorithmRunner(const graphics::Graph& graphics_graph);
        AlgorithmRunner();
        void set_graph(const graphics::Graph& graphics_graph);
        void set_algorithm(std::shared_ptr<Algorithm>& algorithm);
        std::vector<int> run_algorithm();
        std::vector<int> run_bfs(int src);
        std::vector<int> run_dfs(int src);
        std::vector<int> run_topological_sort();
    };
}


#endif