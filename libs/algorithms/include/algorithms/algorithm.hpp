#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_
#include <vector>
#include <graphics/graphics_graph.hpp>
#include <algorithms/traversal.hpp>

namespace algo {
    class Algorithm {
    public:
    virtual ~Algorithm(){};
    virtual Traversal run(const graphics::Graph& graph) = 0;
    };
}


#endif