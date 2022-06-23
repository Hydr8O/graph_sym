#include <algorithms/algorithm_runner.hpp>
#include <iostream>


algo::AlgorithmRunner::AlgorithmRunner() {}

algo::AlgorithmRunner::AlgorithmRunner(const graphics::Graph &graph) {
    m_graph = graph;
}

void algo::AlgorithmRunner::set_graph(const graphics::Graph &graph) {
    m_graph = graph;
}

void algo::AlgorithmRunner::set_algorithm(std::shared_ptr<algo::Algorithm> &algorithm) {
    m_algorithm = algorithm;
}

std::vector<std::shared_ptr<Node>> algo::AlgorithmRunner::run_algorithm() {
    return m_algorithm->run(m_graph);
}
