#ifndef TRAVERSAL_HPP_
#define TRAVERSAL_HPP_

#include <vector>
#include <memory>
#include <graphics/node.hpp>
#include <graphics/edge.hpp>

namespace algo {
    struct Traversal {
        std::vector<std::shared_ptr<Node>> node_traversal;
        std::vector<std::shared_ptr<graphics::Edge>> edge_traversal;
    };
}

#endif