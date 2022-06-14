#ifndef ALGORITHM_RUNNER_HPP_
#define ALGORITHM_RUNNER_HPP_

#include <queue>
#include <algorithms/algo_graph.hpp>
#include <unordered_set>
#include <vector>


namespace algo {
    class AlgorithmRunner {
    private:
        algo::Graph m_algo_graph;
    public:
        AlgorithmRunner(const algo::Graph& algo_graph);
        AlgorithmRunner();
        void set_graph(const algo::Graph& algo_graph);
        std::vector<std::string> run_bfs(const std::string& src);
        std::vector<std::string> run_dfs(const std::string& dst);
    };
}


#endif