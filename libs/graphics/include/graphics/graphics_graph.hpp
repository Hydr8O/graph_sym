#ifndef GRAPHICS_GRAPH_HPP_
#define GRAPHICS_GRAPH_HPP_

#include <graphics/node.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>

typedef std::unordered_map<int, std::shared_ptr<Node>> NodeArray;
namespace graphics {
    class Graph {
        private:
            NodeArray m_nodes;
            int m_node_id= 0;
            std::unordered_set<std::string> m_node_labels;


        public:
            void add_node(std::shared_ptr<Node> node);
            void add_label(std::string label);
            void remove_label(std::string label);
            void print_labels();
            int get_next_node_id() const;
            bool label_exists(const std::string& label);
            const NodeArray& get_nodes() const;
    };
}

#endif