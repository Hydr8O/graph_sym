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
typedef std::unordered_map<int, std::vector<int>> AdjacencyList;
typedef std::unordered_map<int, std::vector<std::pair<float, int>>> WeightedAdjacencyList;
namespace graphics {
    class Graph {
        private:
            NodeArray m_nodes;
            EdgeArray m_edges;
            AdjacencyList m_adjacency_list;
            WeightedAdjacencyList m_weighted_adjacency_list;
            int m_node_id = 0;
            int m_edge_id = 0;
            std::unordered_set<std::string> m_node_labels;

        public:
            void add_node(std::shared_ptr<Node> node);
            void add_edge(std::shared_ptr<Edge> new_edge);
            void create_adjacency_list();
            void create_weighted_adjacency_list();
            void add_path(int src, int dst);
            void add_weighted_path(int src, int dst, float weight);
            void add_label(std::string label);
            void remove_label(std::string label);
            void remove_node(int node_id);
            void remove_edges(int node_id);
            void remove_edge(int edge_id);
            void print_labels();

            int get_next_node_id() const;
            int map_label_to_id(const std::string& label) const;
            
            bool label_exists(const std::string& label);
            bool edge_exsists(const std::shared_ptr<graphics::Edge>& new_edge);

            const NodeArray& get_nodes() const;
            const EdgeArray& get_edges() const;
            const AdjacencyList& get_paths() const;
            const WeightedAdjacencyList& get_weighted_paths() const;

    };
}

#endif