#ifndef DJIKSTRA_HPP_
#define DJIKSTRA_HPP_

#include <unordered_map>
#include <unordered_set>
#include <graphics/graphics_graph.hpp>
#include <algorithms/algorithm.hpp>

namespace algo {
    class Djikstra : public Algorithm{
    private:
        int m_src;
        std::unordered_set<int> m_visited;
        std::unordered_map<int, float> m_distances;

    public:
        Djikstra(int src);
        std::vector<std::shared_ptr<Node>> run(const graphics::Graph& graph) override;
    };
}


#endif