#ifndef DJIKSTRA_HPP_
#define DJIKSTRA_HPP_

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <graphics/graphics_graph.hpp>
#include <algorithms/algorithm.hpp>

namespace algo {
    class Djikstra : public Algorithm{
    private:
        int m_src;
        std::unordered_set<int> m_visited;
        std::unordered_map<int, float> m_distances;
        Traversal m_traversal;
        void init_distances(const WeightedAdjacencyList& adjacency);

    public:
        Djikstra(int src);
        Traversal run(const graphics::Graph& graph) override;
    };
}


#endif