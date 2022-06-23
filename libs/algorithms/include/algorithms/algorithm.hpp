#ifndef ALGORITHM_HPP_
#define ALGORITHM_HPP_
#include <vector>
#include <graphics/graphics_graph.hpp>

namespace algo {
    class Algorithm {
    public:
    virtual ~Algorithm(){};
        virtual std::vector<std::shared_ptr<Node>> run(const graphics::Graph& graph) = 0;
    };
}


#endif