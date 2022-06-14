#ifndef GRAPHICS_GRAPH_HPP_
#define GRAPHICS_GRAPH_HPP_

#include <graphics/node.hpp>
#include <graphics/edge.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

typedef std::unordered_map<int, std::shared_ptr<Node>> NodeArray;
typedef std::unordered_map<int, std::shared_ptr<graphics::Edge>> EdgeArray;
namespace graphics {
    class Graph {
        private:
            NodeArray m_nodes;
            EdgeArray m_edges;
            int m_node_id = 0;
            int m_edge_id = 0;
            std::unordered_set<std::string> m_node_labels;

        public:
            void add_node(std::shared_ptr<Node> node);
            void add_edge(std::shared_ptr<Edge> new_edge);
            void add_label(std::string label);
            void remove_label(std::string label);
            const EdgeArray& get_edges() const;
            void print_labels();
            int get_next_node_id() const;
            
            bool label_exists(const std::string& label);
            bool edge_exsists(const std::shared_ptr<graphics::Edge>& new_edge);
            const NodeArray& get_nodes() const;
    };
}

#endif