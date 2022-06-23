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
        std::shared_ptr<Algorithm> m_algorithm;
    public:
        AlgorithmRunner(const graphics::Graph& graphics_graph);
        AlgorithmRunner();
        void set_graph(const graphics::Graph& graphics_graph);
        void set_algorithm(std::shared_ptr<Algorithm>& algorithm);
        std::vector<std::shared_ptr<Node>> run_algorithm();
    };
}


#endif